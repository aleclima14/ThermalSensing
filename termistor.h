/**
/**
 * @file termistor.cpp
 * @author Alecsander Lima (aleclima14@gmail.com)
 * @brief Library to handle NTC
 * @version 0.1
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __termistor_h
#define __termistor_h

/*****************INCLUDES*****************/
#include "Arduino.h"
#include <math.h>
#include "configuration.h"

/*****************DEFINES*****************/
/*Thermistor definition*/
#define BETA_COEFFICIENT 3950 
#define NTC_100K 100000
#define KELVIN_TEMPERATURE 273.15
#define COMMON_AMBIENT_TEMPERATURE 25 
#define TEMPERATURE_OFFSET_ADJUST 6.5 /*Offset for read correction*/

/*Hardware definition*/
#define VCC 3.3
#define RESISTOR 14100 

/*Circular buffer definition*/
#define FILTER_LENGTH 10

class Termistor
{
  public:
    Termistor (int pin);
    double GetTemperature();
  private:
    int _pin; 
};

/*****************PROTOTYPES*****************/
double GetTemperature ();


#endif
