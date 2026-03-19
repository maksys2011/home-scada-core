from pymodbus.server import StartTcpServer
from pymodbus.datastore import ModbusSequentialDataBlock
from pymodbus.datastore import ModbusServerContext, ModbusDeviceContext
import threading
import time
import random

# ===== Начальные значения сенсоров =====
temperature_livingRoom = 15.0    # HR0
temperature_kitchen = 15.0       # HR1
temperature_bedroom = 15.5       # HR2
temperature_bathroom = 15.0      # HR3
light_livingRoom = 150.0         # HR4
light_kitchen = 150.0            # HR5

# ===== Параметры влияния актуаторов =====
HEATER_POWER = 0.3        # Нагрев за такт (для температуры)
LIGHT_POWER = 15.0        # Увеличение освещенности за такт (шторы открываются)
COOLING_RATE = 0.1        # Естественное охлаждение (не используется напрямую)

# ===== Создание одного PLC (slave 1) =====

# Инициализация coils (6 штук) - все выключены
coils = [0] * 10

# Инициализация holding registers
holding_registers = [
    int(temperature_livingRoom),   # HR0
    int(temperature_kitchen),      # HR1
    int(temperature_bedroom),      # HR2
    int(temperature_bathroom),     # HR3
    int(light_livingRoom),         # HR4
    int(light_kitchen),            # HR5
] + [0] * 4

store = ModbusDeviceContext(
    co=ModbusSequentialDataBlock(0, coils),
    hr=ModbusSequentialDataBlock(0, holding_registers)
)

context = ModbusServerContext({1: store}, single=False)

# ===== Логика обновления сенсоров =====

def update_sensors():
    global temperature_livingRoom, temperature_kitchen, temperature_bedroom, temperature_bathroom
    global light_livingRoom, light_kitchen
    
    while True:
        try:
            # === Читаем состояние всех актуаторов ===
            heater_living = context[1].getValues(1, 0, count=1)[0]      # Coil0
            heater_kitchen = context[1].getValues(1, 1, count=1)[0]     # Coil1
            heater_bedroom = context[1].getValues(1, 2, count=1)[0]     # Coil2
            curtain_living = context[1].getValues(1, 3, count=1)[0]     # Coil3 - шторы в гостиной
            curtain_kitchen = context[1].getValues(1, 4, count=1)[0]    # Coil4 - шторы на кухне
            valve_bathroom = context[1].getValues(1, 5, count=1)[0]     # Coil5 - клапан в ванной

            # ОТЛАДКА - смотрим что пришло от SCADA
            print(f"\n=== Состояние Coils (получено от SCADA) ===")
            print(f"Coil0 (отопление гостиная): {heater_living}")
            print(f"Coil1 (отопление кухня): {heater_kitchen}")
            print(f"Coil2 (отопление спальня): {heater_bedroom}")
            print(f"Coil3 (шторы гостиная): {curtain_living}")
            print(f"Coil4 (шторы кухня): {curtain_kitchen}")
            print(f"Coil5 (клапан ванная): {valve_bathroom}")
            print("="*40)
            
            # ===== ТЕМПЕРАТУРА (как и раньше) =====
            
            # Базовая случайная дельта для всех температур
            base_temp_delta = random.uniform(-0.3, 0.3)
            
            # Гостиная
            temp_delta = base_temp_delta
            if heater_living:
                temp_delta += HEATER_POWER  # Добавляем нагрев
            temperature_livingRoom += temp_delta
            
            # Кухня
            temp_delta = base_temp_delta
            if heater_kitchen:
                temp_delta += HEATER_POWER
            temperature_kitchen += temp_delta
            
            # Спальня
            temp_delta = base_temp_delta
            if heater_bedroom:
                temp_delta += HEATER_POWER
            temperature_bedroom += temp_delta
            
            # Ванная
            temp_delta = base_temp_delta + 0.1  # Ванная всегда чуть теплее
            if valve_bathroom:
                temp_delta += HEATER_POWER * 1.5  # Греется быстрее
            temperature_bathroom += temp_delta
            
            # ===== ОСВЕЩЕННОСТЬ (теперь тоже зависит от актуаторов) =====
            
            # Базовая случайная дельта для освещенности
            # (имитация изменений естественного света)
            base_light_delta = random.uniform(-10, 10)
            
            # Гостиная - свет зависит от штор (Coil3)
            light_delta = base_light_delta
            if curtain_living:
                # Шторы открываются - света становится больше
                light_delta += LIGHT_POWER
            else:
                # Шторы закрыты - может быть небольшое естественное изменение
                light_delta += random.uniform(-5, 5)
            
            light_livingRoom += light_delta
            
            # Кухня - свет зависит от штор (Coil4)
            light_delta = base_light_delta
            if curtain_kitchen:
                light_delta += LIGHT_POWER
            else:
                light_delta += random.uniform(-5, 5)
            
            light_kitchen += light_delta
            
            # ===== Ограничения =====
            temperature_livingRoom = max(15, min(35, temperature_livingRoom))
            temperature_kitchen = max(15, min(35, temperature_kitchen))
            temperature_bedroom = max(15, min(35, temperature_bedroom))
            temperature_bathroom = max(15, min(35, temperature_bathroom))
            
            light_livingRoom = max(0, min(1000, light_livingRoom))
            light_kitchen = max(0, min(1000, light_kitchen))
            
            # ===== Запись в регистры =====
            context[1].setValues(3, 0, [int(temperature_livingRoom)])
            context[1].setValues(3, 1, [int(temperature_kitchen)])
            context[1].setValues(3, 2, [int(temperature_bedroom)])
            context[1].setValues(3, 3, [int(temperature_bathroom)])
            context[1].setValues(3, 4, [int(light_livingRoom)])
            context[1].setValues(3, 5, [int(light_kitchen)])
            
            # Отладка
            print(f"\rT: {int(temperature_livingRoom)}/{int(temperature_kitchen)}/{int(temperature_bedroom)}/{int(temperature_bathroom)}°C "
                  f"L: {int(light_livingRoom)}/{int(light_kitchen)} лк | "
                  f"Heat: {heater_living}{heater_kitchen}{heater_bedroom} "
                  f"Curtain: {curtain_living}{curtain_kitchen}", end="")
            
        except Exception as e:
            print(f"Ошибка: {e}")
        
        time.sleep(2)

# ===== Запуск =====
thread = threading.Thread(target=update_sensors)
thread.daemon = True
thread.start()

print("\n" + "="*70)
print("✅ PLC Server: сенсоры живут своей жизнью + влияние актуаторов")
print("="*70)
print("📊 Сенсоры (Holding Registers):")
print("   HR0 - Температура гостиная")
print("   HR1 - Температура кухня")
print("   HR2 - Температура спальня")
print("   HR3 - Температура ванная")
print("   HR4 - Освещенность гостиная")
print("   HR5 - Освещенность кухня")
print("\n⚙️ Актуаторы (Coils):")
print("   Coil0 - Отопление гостиная (+0.3°C/такт)")
print("   Coil1 - Отопление кухня (+0.3°C/такт)")
print("   Coil2 - Отопление спальня (+0.3°C/такт)")
print("   Coil3 - Шторы гостиная (+15 лк/такт)")
print("   Coil4 - Шторы кухня (+15 лк/такт)")
print("   Coil5 - Клапан ванная (+0.45°C/такт)")
print("\n📋 Логика работы:")
print("   • ВЫКЛ: случайные колебания (±0.3°C, ±10 лк)")
print("   • ВКЛ: добавляется тренд (нагрев/освещение)")
print("   • SCADA сама решает когда включать/выключать")
print("="*70)
print("🌐 Сервер на 0.0.0.0:1503 (Slave 1)")
print("="*70 + "\n")

StartTcpServer(context, address=("0.0.0.0", 1503))
