#include "dht.h"


bool DhtSensor::measure_environment(float *temperature, float *humidity) {
    static unsigned long measurement_timestamp = millis();

    if (millis() - measurement_timestamp > FREQUENCY) {
        if (dht_sensor.measure(temperature, humidity)) {
            measurement_timestamp = millis();
            return true;
        }
    }
    return false;
}
