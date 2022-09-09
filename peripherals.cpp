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

/*INCLUDES*/
#include "peripherals.h"

/*GLOBAL VARIABLES*/
bool flagButtonState = TRUE;
bool statusButton = FALSE;

void initPins (void)
{
    /*Output pins*/
    pinMode (PIN_ENABLE_SENSOR, OUTPUT);

    /*Input pins*/
    pinMode (PIN_BATTERY_MEASURE, INPUT);
    pinMode (PIN_TERMISTOR_CH1, INPUT);
    pinMode (PIN_WALL_CHECK, INPUT);
    pinMode (PIN_DHT_SENSOR, INPUT);
}


/**
 * @brief Read button pin and check boolean state
 * 
 * @return True (Indicates that it is fixed to the wall)
 * @return False (Indicates that it is not fixed to the wall)
 */
bool fWallButtonStatus (void)
{
    statusButton = digitalRead(PIN_WALL_CHECK);

    if (statusButton != flagButtonState)
    {
        flagButtonState = statusButton;
    }
    return flagButtonState;
}

/**
 * @brief Turn on/off enable pin 
 * 
 * @param pin_mode TRUE or FALSE
 */
void fnvEnablePin (bool pin_mode)
{
    digitalWrite (PIN_ENABLE_SENSOR, pin_mode);
}

/**
 * @brief Symmetrical voltage divider to measure battery voltage 
 * 
 * @return Battery Voltage (float) 
 */
float BatteryMeasure (void)
{
     /*Read pin and convert to voltage value*/
    uint16_t batteryValue = analogRead (PIN_BATTERY_MEASURE);
    float batteryVoltage = (batteryValue * VCC / 4095) + BATTERY_OFFSET_CORRECTION;

    /*returns value multiplied by 2*/
    return batteryVoltage * 2;
}
