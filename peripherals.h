/**
 * @file peripherals.cpp
 * @author Alecsander Lima (aleclima14@gmail.com)
 * @brief Tratamento dos dispositivos (sensores e atuadores)
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __peripherals_h
#define __peripherals_h

#include "Arduino.h"
#include "configuration.h"

/*FUNCTION PROTOTYPE*/
void initPins (void);
bool fWallButtonStatus (void);
void fnvEnablePin (bool pin_mode);
float BatteryMeasure (void);

/*DEFINITIONS*/
#define BATTERY_MAX_VOLTAGE 2.0
#define BATTERY_MIN_VOLTAGE 1.5
#define MAX_SCALE_TABLE 100
#define MIN_SCALE_TABLE 0
#define BATTERY_OFFSET_CORRECTION 0.19

#endif
