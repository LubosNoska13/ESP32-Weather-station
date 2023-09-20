#include "mq135.h"

void MqSensor::setup() {
    gass_sensor.setRegressionMethod(1); //_PPM =  a*ratio^b
    gass_sensor.init(); 
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for(int i = 1; i <= 10; i++) {
        gass_sensor.update(); // Update data, the Arduino will read the voltage from the analog pin
        calcR0 += gass_sensor.calibrate(RatioMQ135CleanAir);
        Serial.print(".");
    }
    gass_sensor.setR0(calcR0/10);
    Serial.println("  done!.");
    
    if(isinf(calcR0)) {
        Serial.println("Warning: Connection issue, R0 is infinite (Open circuit detected). Please check your wiring and supply");
        while(1);
    }
    if(calcR0 == 0) {
        Serial.println("Warning: Connection issue found, R0 is zero (Analog pin shorts to ground). Please check your wiring and supply");
        while(1);
    }
}

void MqSensor::readData(JsonDocument& doc) {
    gass_sensor.update(); // Update data, the arduino will read the voltage from the analog pin

    gass_sensor.setA(605.18); gass_sensor.setB(-3.937); // Configure the equation to calculate CO concentration value
    doc["Carbon Monoxide"] = gass_sensor.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

    gass_sensor.setA(77.255); gass_sensor.setB(-3.18); //Configure the equation to calculate Alcohol concentration value
    doc["Alcohol"] = gass_sensor.readSensor(); // SSensor will read PPM concentration using the model, a and b values set previously or from the setup

    gass_sensor.setA(110.47); gass_sensor.setB(-2.862); // Configure the equation to calculate CO2 concentration value
    doc["Carbon Dioxide"] = gass_sensor.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

    gass_sensor.setA(44.947); gass_sensor.setB(-3.445); // Configure the equation to calculate Toluen concentration value
    doc["Toluen"] = gass_sensor.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    
    gass_sensor.setA(102.2 ); gass_sensor.setB(-2.473); // Configure the equation to calculate NH4 concentration value
    doc["NH4"] = gass_sensor.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

    gass_sensor.setA(34.668); gass_sensor.setB(-3.369); // Configure the equation to calculate Aceton concentration value
    doc["Aceton"] = gass_sensor.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    
}
