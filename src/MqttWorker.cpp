#include "MqttWorker.hpp"

MqttWorker::MqttWorker(
    MqttClient &client, 
    MqttSourceConfig &config) :
    client_(client), config_(config)
{}

bool MqttWorker::start()
{
    if(!running_){
       running_ = true; 
       worker_ = std::thread(&MqttWorker::process, this); 
       return true;
    }
    return false;
}

void MqttWorker::stop()
{
   if(!running_){
        return;
   }

   running_ = false;

   if(worker_.joinable()){
        worker_.join();
   }
    
}

std::optional<DataPoint> MqttWorker::getDataPoints(const std::string& topic)
{
    std::lock_guard<std::mutex> lock(mtx_);

    auto it = cache_.find(topic);

    if(it == cache_.end()){
        return std::nullopt;
    }

    return it->second;
}

void MqttWorker::process()
{
    while(running_){
        auto msg = client_.tryConsume();

        if (msg)
        {
            auto topic = (*msg)->get_topic();
            auto new_value = (*msg)->to_string();

            double value = std::stod(new_value);

            std::lock_guard<std::mutex> lock(mtx_);

            cache_[topic] = {value, std::chrono::system_clock::now()};

        }
    }
}

