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
#include "termistor.h"

Termistor::Termistor(int pin)
{
  _pin = pin;
}

/**
 * @brief Use the Steinhart-hart equation to calculate the temperature
 * 
 * @return Calculated temperature (Celsius) 
 */
double Termistor::GetTemperature ()
{
  static int i;
  static double accumulatorSum;
  static double temperatureFilter [FILTER_LENGTH];
  
  double temperatureSensor = analogRead (_pin);

  /*Calculate Rth at 0K*/
  double thermistorResistanceT0 = NTC_100K * exp(-BETA_COEFFICIENT / (KELVIN_TEMPERATURE + COMMON_AMBIENT_TEMPERATURE));
  /*Calculate ADC voltages and thermistor resistance measured*/
  double thermistorVoltage = temperatureSensor * VCC / 4095;
  double thermistorResistance = VCC * RESISTOR / thermistorVoltage - RESISTOR;
  /*Applied the Steinhart-Hart equation to convert resistance to temperature*/
  double kelvinTemperature =  BETA_COEFFICIENT / log (thermistorResistance / thermistorResistanceT0);
  /*Convert Kelvin temperature to degree Celsius*/
  double celsiusTemperature = kelvinTemperature - KELVIN_TEMPERATURE + TEMPERATURE_OFFSET_ADJUST;
  
  /*Sum temperature in array*/
  accumulatorSum = accumulatorSum - temperatureFilter [i] + celsiusTemperature;
  temperatureFilter [i] = celsiusTemperature; 
  /*Restart circular array*/
  if (i++ >= FILTER_LENGTH) i = 0;
  /*Calculate average*/
  celsiusTemperature = accumulatorSum/FILTER_LENGTH;

  return celsiusTemperature;

}
