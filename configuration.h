/**
   @file configuration.h
   @author Alecsander Lima (aleclima14@gmail.com)
   @brief Configuracao de pinos e times
   @version 0.1
   @date 2022-05-10

   @copyright Copyright (c) 2022

*/
#ifndef __configuration_h
#define __configuration_h

#include "Arduino.h"
#include "termistor.h"

/*Boolean settings*/
#define FALSE 0
#define TRUE  1

#define SENDING_INTERVAL 60000 /*Timer for sending data to the server, in miliseconds*/

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  200        /* Time ESP32 will go to sleep (in seconds) */

/*DHT Types*/
#define DHTTYPE DHT22
//#define DHTTYPE DHT11

/*Define PINs of MCU*/
#define PIN_ENABLE_SENSOR  12 
#define PIN_WALL_CHECK 13
#define PIN_DHT_SENSOR 26
#define PIN_TERMISTOR_CH1 34
#define PIN_BATTERY_MEASURE 35

#endif
