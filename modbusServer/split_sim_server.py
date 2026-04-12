from pymodbus.server import StartTcpServer
from pymodbus.datastore import ModbusSequentialDataBlock
from pymodbus.datastore import ModbusServerContext, ModbusSlaveContext
import threading
import time

# Modbus map:
#   Holding Registers:
#       HR0 = Kitchen temperature
#       HR1 = Living room temperature
#       HR2 = Bedroom temperature
#       HR3 = Bathroom temperature
#       HR4 = Hallway temperature
#
#   Coils:
#       Coil0 = Split Kitchen
#       Coil1 = Split Living room
#       Coil2 = Split Bedroom
#       Coil3 = Split Bathroom
#       Coil4 = Split Hallway
#
# Address: 0.0.0.0:1503
# Slave ID: 1
# ==========================================================

temps = [
    18.0,  # Kitchen
    19.5,  # Living room
    17.8,  # Bedroom
    21.0,  # Bathroom
    16.5   # Hallway
]

room_names = [
    "Kitchen",
    "Living",
    "Bedroom",
    "Bathroom",
    "Hallway"
]

HEAT_RATES = [0.30, 0.25, 0.28, 0.20, 0.35]   # °C ON
COOL_RATES = [0.12, 0.10, 0.11, 0.08, 0.14]   # °C OFF

MIN_TEMP = 15.0
MAX_TEMP = 35.0
TICK_SECONDS = 5.0

# ---------- Modbus memory ----------
coils = [0] * 10
holding_registers = [int(t) for t in temps] + [0] * 5

store = ModbusSlaveContext(
    co=ModbusSequentialDataBlock(0, coils),
    hr=ModbusSequentialDataBlock(0, holding_registers),
    zero_mode=True
)

context = ModbusServerContext(slaves={1: store}, single=False)

def clamp(value, min_v, max_v):
    return max(min_v, min(max_v, value))


def update_simulation():
    global temps

    while True:
        try:
            split_states = context[1].getValues(1, 0, count=5)

            # Update temperatures
            for i in range(5):
                if split_states[i]:
                    temps[i] += HEAT_RATES[i]
                else:
                    temps[i] -= COOL_RATES[i]

                temps[i] = clamp(temps[i], MIN_TEMP, MAX_TEMP)

            # Write temperatures to holding registers HR0..HR4 (function code 3)
            for i in range(5):
                context[1].setValues(3, i, [int(temps[i])])

            # Debug output
            print("\n" + "=" * 60)
            print("Split System Simulation Tick")
            print("=" * 60)
            for i in range(5):
                state_str = "ON " if split_states[i] else "OFF"
                print(f"{room_names[i]:<10} | Split: {state_str} | Temp: {temps[i]:>5.2f} °C")
            print("=" * 60)

        except Exception as e:
            print(f"[SIM ERROR] {e}")

        time.sleep(TICK_SECONDS)

thread = threading.Thread(target=update_simulation, daemon=True)
thread.start()

# ---------- Startup info ----------
print("=" * 70)
print("✅ Minimal Split System Simulation Server started")
print("=" * 70)
print("🌐 Address: 0.0.0.0:1503")
print("🆔 Slave ID: 1")
print()
print("📊 Holding Registers (Temperatures):")
print("   HR0 - Kitchen")
print("   HR1 - Living room")
print("   HR2 - Bedroom")
print("   HR3 - Bathroom")
print("   HR4 - Hallway")
print()
print("⚙️ Coils (Split systems):")
print("   Coil0 - Kitchen split")
print("   Coil1 - Living room split")
print("   Coil2 - Bedroom split")
print("   Coil3 - Bathroom split")
print("   Coil4 - Hallway split")
print()
print("📋 Logic:")
print("   Split ON  -> temperature rises")
print("   Split OFF -> temperature falls")
print("=" * 70)

# ---------- Start Modbus TCP server ----------
StartTcpServer(context=context, address=("0.0.0.0", 1503))