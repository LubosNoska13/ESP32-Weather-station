#include <Arduino.h>

//  
#include <icons.h>
#include <config.h>
#include <display.h>
#include <dht.h>
#include <mq135.h>
#include <setwifi.h>
#include <mqtt.h>

// Json string library
#include <ArduinoJson.h>

// Create a JSON document
DynamicJsonDocument doc(256);

void setup() {
  // Set serial monitor
  Serial.begin(115200);

  setup_mq135();
  setup_display();
  
  // Initialize Wi-Fi
  wifi_setup();
  // scan_network();
  connect_to_wifi(ssid, password);

  mqtt_connection(mqttServer, mqttPort, mqttUser, mqttPassword);
}

void loop() {
  client.loop();
  float temperature;
  float humidity;
  static int idx = 0;
  
  /* Measure temperature and humidity.  If the functions returns
      true, then a measurement is available. */
  if (measure_environment(&temperature, &humidity)) {

    // Calibrate values
    temperature -= 4.8;
    humidity += 12;

    // Wifi rssi conection 
    int32_t rssi = WiFi.RSSI(); 

    MQ135.update(); // Update data, the arduino will read the voltage from the analog pin

    MQ135.setA(605.18); MQ135.setB(-3.937); // Configure the equation to calculate CO concentration value
    float CO = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

    MQ135.setA(77.255); MQ135.setB(-3.18); //Configure the equation to calculate Alcohol concentration value
    float Alcohol = MQ135.readSensor(); // SSensor will read PPM concentration using the model, a and b values set previously or from the setup

    MQ135.setA(110.47); MQ135.setB(-2.862); // Configure the equation to calculate CO2 concentration value
    float CO2 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

    MQ135.setA(44.947); MQ135.setB(-3.445); // Configure the equation to calculate Toluen concentration value
    float Toluen = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    
    MQ135.setA(102.2 ); MQ135.setB(-2.473); // Configure the equation to calculate NH4 concentration value
    float NH4 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

    MQ135.setA(34.668); MQ135.setB(-3.369); // Configure the equation to calculate Aceton concentration value
    float Aceton = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    
    // Set the values of the fields
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["co"] = CO;
    doc["device"] = device;
    doc["wifi"] = rssi;
    doc["alcohol"] = Alcohol;
    doc["co2"] = CO2;
    doc["toluen"] = Toluen;
    doc["nh4"] = NH4;
    doc["aceton"] = Aceton;

    if (idx == 1){
      displayData("Temperature", temperature_icon, 50, temperature, rssi);
    } else if (idx == 2){
      displayData("Humidity", humidity_icon, 52, humidity, rssi);
    } else if (idx == 3){
      displayData("Carbon Monoxide", co_icon, 70, CO, rssi);
    } else if (idx == 4){
      displayData("Carbon Dioxide", co2_icon, 70, CO2, rssi);
      idx = -1;
    }
    String json_string;
    // Serialize the JSON document to a string
    serializeJson(doc, json_string);

    // Print the JSON string
    Serial.println(json_string);

    // Publish data
    client.publish(mqttTopic, json_string.c_str());

    idx += 1;
  }
  
}
