#ifndef DHT_H
#define DHT_H

// DHT11 (temperature, humidity) library
#include "DHT_Async.h"

extern DHT_Async dht_sensor;

bool measure_environment(float *temperature, float *humidity);

#endif