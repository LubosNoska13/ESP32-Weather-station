// === Library
#include <Arduino.h>
// Json string library
#include <ArduinoJson.h>

// Oled display library
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// DHT11 (temperature, humidity) library
#include <Arduino.h>
#include "DHT_Async.h"

// MQ135 (gass sensor) library
#include <MQUnifiedsensor.h>

// MQTT library
#include <WiFi.h>
#include <PubSubClient.h>

// === Definitions
// Oled display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// DHT11 settings
#define DHT_SENSOR_TYPE DHT_TYPE_11
static const int DHT_SENSOR_PIN = 4;

// MQ135 settings
#define placa "ESP-32"
#define Voltage_Resolution 3.3
#define pin 39 // Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 12 
#define RatioMQ135CleanAir 3.6 // RS / R0 = 3.6 ppm  

// Wifi settings
static const char* const ssid = "";
static const char* const password = "";

// MQTT settings
static const char* const mqttServer = "";
static const int mqttPort = 1883;
static const char* const mqttUser = "";
static const char* const mqttPassword = "";
static const char* const mqttTopic = "";

// Generall settings
static const char* const device = "ESP32";

// Create a JSON document
DynamicJsonDocument doc(256);

// === Instance
// Oled display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT11
DHT_Async dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// MQ135
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

// Wifi, mqtt
WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  // Set serial monitor
  Serial.begin(115200);

  // ============================================================
  //Set math model to calculate the PPM concentration and the value of constants
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

  // ============================================================
  // Display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  
  // Wifi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Mqtt connection
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

static bool measure_environment(float *temperature, float *humidity) {
    static unsigned long measurement_timestamp = millis();

    /* Measure once every four seconds. */
    if (millis() - measurement_timestamp > 4000ul) {
        if (dht_sensor.measure(temperature, humidity)) {
            measurement_timestamp = millis();
            return (true);
        }
    }

    return (false);
}

void loop() {
  client.loop();
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
      true, then a measurement is available. */
  if (measure_environment(&temperature, &humidity)) {

    // Calibrate values
    temperature -= 1.5;
    humidity += 7;
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    // Wifi rssi conection 
    int32_t rssi = WiFi.RSSI();
    display.setCursor(0, 0);
    if (rssi >= -70){
      // Serial.println("Very good");
      display.print("Wifi: Very good");
    }
    else if (rssi >= -70){
      display.print("Wifi: Good");
    }
    else if (rssi >= -90){
      display.print("Wifi: Bad");
    }
    else {
      display.print("Wifi: No signal");
    }
    display.setCursor(0, 10);
    display.print("Temperature = ");
    display.print(temperature);
    display.print("C");

    display.setCursor(0, 20);
    display.print("Humidity = ");
    display.print(humidity);
    display.print("%");

    display.display(); 

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

    // Serialize the JSON document to a string
    String json_string;
    serializeJson(doc, json_string);

    // Print the JSON string
    Serial.println(json_string);

    // Publish data
    client.publish(mqttTopic, json_string.c_str());

  }
  
}
