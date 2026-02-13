from pymodbus.server import StartTcpServer
from pymodbus.datastore import ModbusSequentialDataBlock
from pymodbus.datastore import ModbusServerContext, ModbusDeviceContext
import time
import threading
import random

temp_value = 22.5
light_value = 350.0

store1 = ModbusDeviceContext(hr=ModbusSequentialDataBlock(0, [22]*10))
store2 = ModbusDeviceContext(hr=ModbusSequentialDataBlock(0, [350]*10))

context = ModbusServerContext({1: store1, 2: store2}, single=False)

def update_sensors():
    global temp_value, light_value
    while True:
        temp_value += random.uniform(-0.5, 0.5)
        light_value += random.uniform(-10, 10)

        context[1].setValues(3, 0, [int(temp_value)])
        context[2].setValues(3, 0, [int(light_value)])

        time.sleep(2)

print("✅ Modbus TCP server started on 127.0.0.1:1502")
threading.Thread(target=update_sensors, daemon=True).start()

StartTcpServer(context=context, address=("127.0.0.1", 1502))


