#include <iostream>
#include "PgArchive.hpp"

PgArchive::PgArchive(const std::string &connInfo) 
    : Archive(std::string("pg_archive_dummy"))
{
    connect(connInfo);
    worker_ = std::thread(&PgArchive::processQueue, this);
}

PgArchive::~PgArchive()
{
    {
        std::lock_guard<std::mutex>lock(mtx_);
        running_ = false;
    }

    cv_.notify_one();

    if(worker_.joinable()){
        worker_.join();
    }
    
    if(conn_){
        PQfinish(conn_);
        conn_ = nullptr;
    }

    std::cout << "[PostgreSQL] Disconnected\n";
}

void PgArchive::appendArchive(
    const std::string& id, 
    const std::string& nameSensor, 
    double value, 
    State state)
{
    std::string stateSensor = StateToString(state);
    data record;
    record.sensorId = id;
    record.sensorName = nameSensor;
    record.value = value;
    record.state = stateSensor;

    {
        std::lock_guard<std::mutex>lock(mtx_);
        queue_.push(record);
    }

    cv_.notify_one();
    
}

void PgArchive::processQueue()
{
    while(true){
        std::unique_lock<std::mutex> lock(mtx_);
        
        while(queue_.empty() && running_){
            cv_.wait(lock);
        }

        if(!running_ && queue_.empty()) break;

        data rec = queue_.front();
        queue_.pop();

        lock.unlock();

        std::string query =
        "INSERT INTO archive(sensor_id, sensor_name, value, state) VALUES('" +
        rec.sensorId + "','" + rec.sensorName + "'," + std::to_string(rec.value) + ",'" +
        rec.state + "')";

        PGresult* result = PQexec(conn_, query.c_str());
        
        if (PQresultStatus(result) != PGRES_COMMAND_OK) {
            std::cerr << "PostgreSQL INSERT failed: "
                      << PQerrorMessage(conn_) << std::endl;
        }

        PQclear(result);
    }
}

void PgArchive::connect(const std::string& connInfo)
{
    conn_ = PQconnectdb(connInfo.c_str());

    if(PQstatus(conn_) != CONNECTION_OK){

        std::cerr << "PostgreSQL connection failed: "
                  << PQerrorMessage(conn_) << std::endl;

        PQfinish(conn_);
        conn_ = nullptr;

        throw std::runtime_error("PostgreSQL connection failed: ");
    }
}
