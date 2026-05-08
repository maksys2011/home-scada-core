#include "MqttWorker.hpp"

MqttWorker::MqttWorker(
    MqttClient &client) :
    client_(client)
{}

MqttWorker::~MqttWorker() noexcept
{
    stop();
}

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

        if (msg && *msg != nullptr)
        {
            auto topic = (*msg)->get_topic();
            auto new_value = (*msg)->to_string();

            double value = std::stod(new_value);

            std::lock_guard<std::mutex> lock(mtx_);

            DataPoint data;

            data.value = value;
            data.timestamp = std::chrono::system_clock::now();

            cache_[topic] = data;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

