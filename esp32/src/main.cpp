#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "dht.h"
#include "mq135.h"
#include "setwifi.h"
#include "mqtt.h"
#include <ArduinoJson.h>

// Create instances 
Display main_display;
MqSensor gass_sensor;
DhtSensor temp_sensor;
WifiConnection wifi;
MqttConnection mqtt;

// Make static json object with 10 items
const size_t capacity = JSON_OBJECT_SIZE(10);
StaticJsonDocument<capacity> doc;

void setup() {
  // Set serial monitor
  Serial.begin(115200);

  // Setup
  gass_sensor.setup();
  main_display.setup();
  wifi.setup();

  // Connect to wifi
  wifi.scan_network();
  wifi.connect();

  // Connect to Mqtt
  mqtt.connect();
}

void loop() {
  mqtt.client.loop();

  float temperature;
  float humidity;
  static int8_t idx = 0;
  
  /* 
    Measure temperature and humidity.  If the functions returns
    true, then a measurement is available. 
  */
  if (temp_sensor.measure_environment(&temperature, &humidity)) {

    // Calibrate values
    temperature -= 4.8;
    humidity += 12;

    // Wifi rssi conection 
    int32_t rssi = WiFi.RSSI(); 

    // Read gasses from the air and store this informations in the json object
    gass_sensor.readData(doc);

    // Fill data into json object
    doc["Temperature"] = temperature;
    doc["Humidity"] = humidity;
    doc["Device"] = device;
    doc["Wifi"] = rssi;
    
    /*
      Loop though gass informations on the oled display
    */
    if (idx > 3){
      idx = 0;
    }
    main_display.showData(doc, &idx);

    // Serialize the JSON document to a string
    String json_string;
    serializeJson(doc, json_string);

    // Print the JSON string to console
    Serial.println(json_string);

    // Publish data
    mqtt.client.publish(mqttTopic, json_string.c_str());

    idx++;
  }
  
}
