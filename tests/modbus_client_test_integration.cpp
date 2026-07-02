#include "ModbusClient.hpp"
#include "ModbusClientConfig.hpp"
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>
#include <modbus/modbus.h>
using json = nlohmann::json;

static json makeJsonModbusClient()
{
    json j{
        {"client_id" , "100"},
        {"name" , "PlC_owen"},
        {"ip" , "127.0.0.1"},
        {"port" , 15020},
        {"slave_id" , 1}
    }; 
    return j;
}

class Server
{
    public:

    Server(std::string ip, int port)
    {
        
        ctx_ = modbus_new_tcp(ip.c_str(), port);
        mapping_ = modbus_mapping_new(10, 10, 10, 10);

        if(!ctx_) throw std::runtime_error("modbus_new_tcp failed");
            
        if(!mapping_) throw std::runtime_error("modbus_mapping_new failed");

        mapping_->tab_bits[0] = 1;
        mapping_->tab_input_bits[0] = 0;
        mapping_->tab_input_registers[0] = 98;
        mapping_->tab_registers[0] = 99;

        socket_ser = modbus_tcp_listen(ctx_, 1);

        if(socket_ser == -1) throw std::runtime_error("modbus_tcp_listen failed");
        
    }

    ~Server()
    {
        server_stop();
    }

    void server_start()
    {
        socket_cli  = modbus_tcp_accept(ctx_, &socket_ser);
        
        if (socket_cli == -1) return;

        
        uint8_t query[260];

        int rc = modbus_receive(ctx_, query);

        if (rc > 0) modbus_reply(ctx_, query, rc, mapping_);
        else return;
        
    }

    void server_start_loop()
    {
        socket_cli  = modbus_tcp_accept(ctx_, &socket_ser);
        
        if (socket_cli == -1) return;

        while(true)
        {
            uint8_t query[260];

            int rc = modbus_receive(ctx_, query);

            if (rc > 0) modbus_reply(ctx_, query, rc, mapping_);
            else break;
        }
    
    }

    void server_stop(){

        if (socket_cli != -1) close(socket_cli);

        if (socket_ser != -1) close(socket_ser);

        if (mapping_) modbus_mapping_free(mapping_);

        if (ctx_) modbus_free(ctx_);

        mapping_ = nullptr;
        ctx_ = nullptr;

        socket_ser = -1;
        socket_cli = -1;
    }

    void setMapping(int nb_bits,
                    int nb_input_bits,
                    int nb_register,
                    int nb_input_registers){
        mapping_ = modbus_mapping_new(nb_bits,
                                      nb_input_bits,
                                      nb_register,
                                      nb_input_registers);

    }

    modbus_mapping_t*& getMapping() {return mapping_;};

    private:

    modbus_t* ctx_ = nullptr;
    modbus_mapping_t* mapping_ = nullptr;
    int socket_ser = -1;
    int socket_cli = -1;
    std::atomic_bool stop_;
};

TEST(ModbusClientIntegrationTest, ModbusClientConnect)
{
    ModbusClientConfig cfg;
    auto j = makeJsonModbusClient();
    cfg.fromJson(j);
    ModbusClient client(cfg);

    EXPECT_FALSE(client.connect());
}

TEST(ModbusClientIntegrationTest, ModbusClientConnectToServer)
{
    ModbusClientConfig cfg;
    auto j = makeJsonModbusClient();
    cfg.fromJson(j);

    ModbusClient client(cfg);
    
    std::string ip = cfg.getIp();
    int port = cfg.getPort();
    
    Server server_modbus(ip, port);

    std::thread worker([&server_modbus]()
    {
        server_modbus.server_start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    EXPECT_TRUE(client.connect());

    client.disconnect();

    server_modbus.server_stop();

    std::this_thread::sleep_for(std::chrono::microseconds(300));

    worker.join();
}

TEST(ModbusClientIntegrationTest, ReadHoldingRegister)
{
    ModbusClientConfig cfg;
    auto j = makeJsonModbusClient();
    cfg.fromJson(j);

    ModbusClient client(cfg);
    
    std::string ip = cfg.getIp();
    int port = cfg.getPort();
    
    Server server_modbus(ip, port);

    std::thread worker([&server_modbus]()
    {
        server_modbus.server_start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    ASSERT_TRUE(client.connect());

    EXPECT_EQ(client.readHolding(0), 99);

    client.disconnect();

    server_modbus.server_stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    worker.join();
}

TEST(ModbusClientIntegrationTest, ReadInputRegister)
{
    ModbusClientConfig cfg;
    auto j = makeJsonModbusClient();
    cfg.fromJson(j);

    ModbusClient client(cfg);
    
    std::string ip = cfg.getIp();
    int port = cfg.getPort();
    
    Server server_modbus(ip, port);

    std::thread worker([&server_modbus]()
    {
        server_modbus.server_start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    ASSERT_TRUE(client.connect());

    EXPECT_EQ(client.readInput(0), 98);

    client.disconnect();

    server_modbus.server_stop();

    worker.join();
}

TEST(ModbusClientIntegrationTest, ReadCoilRegister)
{
    ModbusClientConfig cfg;
    auto j = makeJsonModbusClient();
    cfg.fromJson(j);

    ModbusClient client(cfg);
    
    std::string ip = cfg.getIp();
    int port = cfg.getPort();
    
    Server server_modbus(ip, port);

    std::thread worker([&server_modbus]()
    {
        server_modbus.server_start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    ASSERT_TRUE(client.connect());

    EXPECT_TRUE(client.readCoil(0));

    client.disconnect();

    server_modbus.server_stop();

    worker.join();
}

TEST(ModbusClientIntegrationTest, ReadDiscreteRegister)
{
    ModbusClientConfig cfg;
    auto j = makeJsonModbusClient();
    cfg.fromJson(j);

    ModbusClient client(cfg);
    
    std::string ip = cfg.getIp();
    int port = cfg.getPort();
    
    Server server_modbus(ip, port);

    std::thread worker([&server_modbus]()
    {
        server_modbus.server_start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    ASSERT_TRUE(client.connect());

    EXPECT_FALSE(client.readDiscrete(0));

    client.disconnect();

    server_modbus.server_stop();

    worker.join();
}

TEST(ModbusClientIntegrationTest, WriteRegister)
{  
    ModbusClientConfig cfg;
    auto j = makeJsonModbusClient();
    cfg.fromJson(j);

    ModbusClient client(cfg);
    
    std::string ip = cfg.getIp();
    int port = cfg.getPort();
    
    Server server_modbus(ip, port);

    std::thread worker([&server_modbus]()
    {
        server_modbus.server_start_loop();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    ASSERT_TRUE(client.connect());

    int value = 150;

    EXPECT_NO_THROW(client.writeRegister(0, value));
    
    EXPECT_EQ(client.readHolding(0), value);

    client.disconnect();

    server_modbus.server_stop();

    worker.join();
}







