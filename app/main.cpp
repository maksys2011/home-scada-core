#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"
#include "RandomSource.hpp"
#include "Logger.hpp"
#include "Archive.hpp"
#include "SensorManager.hpp"
#include "SmoothRandomSource.hpp"
#include "testSource.hpp"
#include "ArchiveReader.hpp"
#include "ArchiveReport.hpp"

using json = nlohmann::json;

int main() {

    SensorManager manager;
    const std::string filePath = "/home/maksys2011/home-scada/configTest.json/SensorConfig.json";
    const std::string fileLoggerPath = "/home/maksys2011/home-scada/logs/events.log";
    const std::string fileArchivePath = "/home/maksys2011/home-scada/archive/archive.csv";
    SensorConfig cfg;
    cfg.fromJson(filePath);
    Logger log(fileLoggerPath);
    Archive arch(fileArchivePath);
    SmothRandomSource source(50.0, 0.2, 48.0, 52.0);
    Sensor sensors(cfg, &log, &arch, &source);
    manager.addSensor(cfg.getId(), &sensors);
    for(size_t i = 0; i < 100; i++){
        manager.tick();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "<< STOP >>" << std::endl;

    const std::string arch_path = "/home/maksys2011/home-scada/archive/archive.csv";
    ArchiveReader r(arch_path);

    const std::string& file = "/home/maksys2011/home-scada/archive/arch.txt";
    auto records = r.readAll();
    ArchiveReport::writeSummaryToFile(records, file);

    
    return 0;
}
