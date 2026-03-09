#include <iostream>
#include "PgArchive.hpp"

PgArchive::PgArchive(const std::string &connInfo) 
    : Archive(std::string("pg_archive_dummy"))
{
    conn_ = PQconnectdb(connInfo.c_str());
    if(PQstatus(conn_) != CONNECTION_OK){
         std::cerr << "PostgreSQL connection failed: "
                  << PQerrorMessage(conn_) << std::endl;
    }
}

PgArchive::~PgArchive()
{
    if(conn_){
        PQfinish(conn_);
    }
}

void PgArchive::appendArchive(
    const std::string& Id, 
    const std::string& nameSensor, 
    double value, 
    State state)
{
    std::string query =
        "INSERT INTO archive(sensor_id, sensor_name, value, state) VALUES('" +
        Id + "','" + nameSensor + "'," + std::to_string(value) + ",'" +
        StateToString(state) + "')";

    PQexec(conn_, query.c_str());
}
