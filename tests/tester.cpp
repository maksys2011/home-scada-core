#include "tester.hpp"
#include "Logger.hpp"
#include "Archive.hpp"
#include "SensorConfig.hpp"
#include "testSource.hpp"
#include "Sensor.hpp"
#include "SensorManager.hpp"
#include <vector>

void Tester::runBasicFlow()
{
    Logger log("../logs/events.log");
    Archive arch("../archive/archive.csv");
    SensorConfig cfg;
    const std::string pathFile = "../SensorConfig.json";
    cfg.fromJson(pathFile);
    std::vector<double>values = {50,51,52};
    testSource test(values);
    Sensor sensors(cfg, &log, &arch, &test);
    SensorManager manager;
    manager.addSensor(cfg.getId(), &sensors);
    for(size_t i = 0; i < values.size(); i++){
        manager.tick();}
}