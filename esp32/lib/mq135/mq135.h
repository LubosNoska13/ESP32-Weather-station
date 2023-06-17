#ifndef MQ135_H
#define MQ135_H

// MQ135 (gass sensor) library
#include <MQUnifiedsensor.h>

// MQ135 settings
const char* placa = "ESP-32";
#define Voltage_Resolution 3.3
#define pin 39 // Analog input 0 of your arduino
const char* type = "MQ-135";
#define ADC_Bit_Resolution 12 
#define RatioMQ135CleanAir 3.6 // RS / R0 = 3.6 ppm 

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup_mq135(){
    MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
    MQ135.init(); 
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for(int i = 1; i<=10; i++)
    {
        MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
        calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
        Serial.print(".");
    }
    MQ135.setR0(calcR0/10);
    Serial.println("  done!.");
    
    if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
    if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
}

#endif