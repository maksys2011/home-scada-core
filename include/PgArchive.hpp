#pragma once
#include <libpq-fe.h>
#include <string>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include "Archive.hpp"

struct data{
    std::string sensorId;
    std::string sensorName;
    double value;
    std::string state;
};

class PgArchive : public Archive
{
public:
    PgArchive(const std::string& connInfo);
    ~PgArchive();

    void appendArchive(
        const std::string& id,
        const std::string& nameSensor,
        double value,
        State state
    ) override;

    void processQueue();
    void connect(const std::string& connInfo);


private:
    PGconn* conn_ = nullptr;
    std::mutex mtx_;
    std::queue<data> queue_;
    bool running_ = true;
    std::condition_variable cv_;
    std::thread worker_;
};
