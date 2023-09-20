#ifndef DHT_H
#define DHT_H

#include "DHT_Async.h"
#include "config.h"

/*
    Class for reading data (temperature and humidity) from the air.
    Device: DHT11
*/

class DhtSensor {
    private:
        // Choose your DHT sensor 
        enum DHT_Type {
            DHT11,
            DHT12,
            DHT21,
            DHT22
        };
        const uint8_t PIN = 4;
        DHT_Type type = DHT11;
        DHT_Async dht_sensor;
        const uint16_t FREQUENCY = frequency_of_reading_data;
    public:
        DhtSensor() : dht_sensor(PIN, type) {}
        // Method to read humidity and temperature
        bool measure_environment(float *temperature, float *humidity);
};


#endif // DHT_H