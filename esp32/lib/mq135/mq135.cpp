#include "mq135.h"

// MQ135 (gas sensor) settings
const char* placa = "ESP-32";
#define Voltage_Resolution 3.3
#define pin 39 // Analog input 0 of your Arduino
const char* type = "MQ-135";
#define ADC_Bit_Resolution 12 
#define RatioMQ135CleanAir 3.6 // RS / R0 = 3.6 ppm 

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup_mq135() {
    MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
    MQ135.init(); 
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for(int i = 1; i <= 10; i++) {
        MQ135.update(); // Update data, the Arduino will read the voltage from the analog pin
        calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
        Serial.print(".");
    }
    MQ135.setR0(calcR0/10);
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
