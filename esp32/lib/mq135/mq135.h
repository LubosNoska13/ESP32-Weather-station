#ifndef MQ135_H
#define MQ135_H

#include <MQUnifiedsensor.h>
#include <ArduinoJson.h>

/*
    Class for reading gasses from the air.
    Device: MQ135 
    This device require a pre-heat for 24 hours.
*/

class MqSensor {
    private:
        // Default values for gas sensor
        const char* placa = "ESP-32";               // Name of using MCU
        const float Voltage_Resolution = 3.3;       // Power voltage
        const uint8_t PIN = 39;                     // Analog input 0 of your Arduino
        const char* type = "MQ-135";                // Type of MQ series sensor
        const uint8_t ADC_Bit_Resolution = 12;      // Analog to Digital Convertor resolution
        const float RatioMQ135CleanAir = 3.6;       // RS / R0 = 3.6 ppm 
        MQUnifiedsensor gass_sensor;

    public:
        MqSensor() : gass_sensor(placa, Voltage_Resolution, ADC_Bit_Resolution, PIN, type) {}
        // Method that needs to be called at startup
        void setup();
        // Method to read all gases from the air and
        // store this information on a json object.
        void readData(JsonDocument& doc);
};

#endif // MQ135_H
