#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"
#include "RandomSource.hpp"
#include "Logger.hpp"
#include "SensorManager.hpp"
using json = nlohmann::json;

int main() {

    Logger log("../logs/events.log");
    
    log.logStateChange("s1", State::OK, State::WARN, 10.0);
    log.logStateChange("s1", State::WARN, State::ALARM, 20.0);
    log.logStateChange("s1", State::ALARM, State::OK, 5.0);

}
