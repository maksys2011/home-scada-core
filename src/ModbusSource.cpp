#include "ModbusSource.hpp"

ModbusSource::ModbusSource(
    const std::string &ip, 
    int port, 
    int slaveId, 
    int startAddress)
    :
    ip_(ip),
    port_(port),
    slaveId_(slaveId),
    startAddress_(startAddress)
{}

ModbusSource::~ModbusSource()
{
    modbus_free(ctx_);
}

bool ModbusSource::connect()
{
    return false;
}

void ModbusSource::disconnect()
{
}

double ModbusSource::readValue()
{
    /*ctx_ = modbus_new_tcp(ip_, port_);
    if(!ctx){
        std::cerr << "modbus_new_tcp failed\n";
        return -1;
    }

     if(modbus_connect(ctx_) == -1){
        std::cerr << "modbus_connect failed: "
                  << modbus_strerror(errno) << "\n";
        connected_ = false;
        return 1;
    }*/
    return 0.0;
}
