#include <iostream>
#include <modbus/modbus.h>
#include <errno.h>
#include <cstring>

int main()
{
    const char* ip = "127.0.0.1";
    const int port = 1502;

    modbus_t* ctx = modbus_new_tcp(ip, port);
    if(!ctx){
        std::cerr << "modbus_new_tcp failed\n";
        return 1;
    }

    if(modbus_connect(ctx) == -1){
        std::cerr << "modbus_connect failed: "
                  << modbus_strerror(errno) << "\n";
        modbus_free(ctx);
        return 1;
    }

    modbus_set_slave(ctx, 1);

    uint16_t regs[10] = {0};

    int rc = modbus_read_registers(ctx, 0, 5, regs);
    
    if(rc == -1){
        std::cerr << "modbus_read_registers failed: "
                  << modbus_strerror(errno) << "\n";
    } else {
        
        for(int i = 0; i < rc; ++i)
            std::cout << "HR[" << i << "] = " << regs[i] << "\n";
    }

    rc = modbus_read_input_registers(ctx, 0, 4, regs);
    if(rc == -1){
        std::cerr << "modbus_read_input_registers failed: "
                  << modbus_strerror(errno) << "\n";
    } else {
        std::cout << "Read " << rc << " input registers:\n";
        for(int i = 0; i < rc; ++i)
            std::cout << "IR[" << i << "] = " << regs[i] << "\n";
    }

    modbus_close(ctx);
    modbus_free(ctx);
    return 0;
}

