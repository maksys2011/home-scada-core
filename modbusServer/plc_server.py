from pymodbus.server import StartTcpServer
from pymodbus.datastore import ModbusSequentialDataBlock
from pymodbus.datastore import ModbusServerContext, ModbusDeviceContext
import threading
import time
import random

# ===== Начальные значения =====

temperature = 20.0
light = 300.0

# ===== Создание одного PLC (slave 1) =====

store = ModbusDeviceContext(
    co=ModbusSequentialDataBlock(0, [0]*10),   # coils (дискретные выходы)
    # hr=ModbusSequentialDataBlock(0, [0]*10)    # holding registers
    hr=ModbusSequentialDataBlock(0, [int(temperature), int(light)] + [0]*8)
)

context = ModbusServerContext({1: store}, single=False)

# ===== Логика обновления PLC =====

def update_plc():
    global temperature, light

    while True:
        # Читаем состояние актуаторов
        heater_on = context[1].getValues(1, 0, count=1)[0]        # Coil0
        curtain_percent = context[1].getValues(3, 2, count=1)[0]  # HR2

        # Температура зависит от отопления
        if heater_on:
            temperature += 1
        else:
            temperature += random.uniform(-1, 1)

        # Свет зависит от положения шторы
        #light = 100 + curtain_percent * 5 + random.uniform(-10, 10)
        light = 300 + curtain_percent * 5 + random.uniform(-10, 10)

        # Записываем значения датчиков
        context[1].setValues(3, 0, [int(temperature)])  # HR0
        context[1].setValues(3, 1, [int(light)])        # HR1

        time.sleep(2)

# ===== Запуск фонового обновления =====

thread = threading.Thread(target=update_plc)
thread.daemon = True
thread.start()

# ===== Запуск Modbus TCP сервера =====


print("✅ PLC started on 0.0.0.0:1503 (Slave 1)")
StartTcpServer(context, address=("0.0.0.0", 1503))
