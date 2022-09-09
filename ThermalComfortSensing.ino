/**
   @file ThermalComfortSensing.ino
   @author Alecsander Lima (aleclima14@gmail.com)
   @brief
   Projeto de TCC desenvolvido por Alecsander Lima
   Rede de sensoriamento com enfase em coleta de dados de temperatura de
   superficie de paredes para estudo de conforto térmico em edificações urbanas.
   @version 0.1
   @date 2022-05-10

   @copyright Copyright (c) 2022

*/

/*INCLUDES*/
#include "configuration.h"
#include "termistor.h"
#include <DHT.h>
#include "peripherals.h"
#include <ArduinoJson.h>
#include "EspMQTTClient.h"

/*DEFINES*/
// #define SERIAL_DEBUG

/*FUNCTIONS*/
void fnvSendingMQTTServer (void);
void fnvPublishJSONVariables (void);

/*SETUP*/
Termistor SensorCH1(PIN_TERMISTOR_CH1);
DHT dht(PIN_DHT_SENSOR, DHTTYPE);

/*GLOBAL VARIABLES*/
double WallMeasureTemperature;
double DHTMeasureTemperature;
double DHTMeasureHumidity;

float BatteryLevel;

unsigned long timerCount1 = 0;

int WallButtonStatus;
int timerControl = FALSE;

char temperatureSurface [100];
char temperatureAmbient [100];
char humidityAmbient [100];
char buttonStatus [100];
char batteryLevel [100];


EspMQTTClient client
(
  "ssd id",                                   //Wifi SSID
  "password ",                                //Wifi password
  "mqtt.tago.io",                             //MQTT Broker Server
  "Default",                                  //Username
  "68468d77-4172-4355-ab59-6babda54162c",     //Device Token 
  "Wall Temperature Logger",                  //Client name 
  1883                                        //The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  initPins();
  dht.begin();
#ifdef SERIAL_DEBUG
  Serial.begin(9600);
#endif

  fnvSendingMQTTServer ();

  digitalWrite (PIN_ENABLE_SENSOR, HIGH);
}

void onConnectionEstablished()
{}

void loop()
{
  fnvEnablePin(TRUE);
  WallMeasureTemperature = SensorCH1.GetTemperature();
  DHTMeasureTemperature = dht.readTemperature();
  DHTMeasureHumidity = dht.readHumidity();
  WallButtonStatus = fWallButtonStatus();
  BatteryLevel = BatteryMeasure();


#ifdef SERIAL_DEBUG
  Serial.println (String ("Surface: ") + String (WallMeasureTemperature, 2) +
                  String (" Temperature: ") + String (DHTMeasureTemperature, 2) +
                  String (" Humidity: ") + String (DHTMeasureHumidity, 2) +
                  String (" WallButton: ") + String (WallButtonStatus) +
                  String (" BatteryLevel: ") + String (BatteryLevel));
  delay(1000);

#else

  if ((millis() - timerCount1) > SENDING_INTERVAL)
  {
    fnvPublishJSONVariables ();
    fnvSendingMQTTServer ();

    timerCount1 = millis();

    /*Set a flag after sending data to start deep sleep mode*/
    timerControl = TRUE;
  }

  client.loop();

  if (timerControl == TRUE)
  {
    timerControl = FALSE;
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
  }

#endif
}

void fnvSendingMQTTServer (void)
{
  /*Sending data to MQTT server*/
  client.publish  ("info/temperatureSurface", temperatureSurface);
  delay(20);
  client.publish  ("info/temperatureAmbient", temperatureAmbient);
  delay(20);
  client.publish  ("info/humidityAmbient"   , humidityAmbient   );
  delay(20);
  client.publish  ("info/buttonStatus"      , buttonStatus      );
  delay(20);
  client.publish  ("info/batteryLevel"      , batteryLevel      );
  delay(20);
}

void fnvPublishJSONVariables (void)
{
  /*Temperature Surface Sensor Data*/
  StaticJsonDocument<300> temperatureSurface_;
  temperatureSurface_["variable"] = "tempSurface";
  temperatureSurface_["value"] = WallMeasureTemperature;
  serializeJson(temperatureSurface_, temperatureSurface);

  /*Ambient Temperature Sensor Data*/
  StaticJsonDocument<300> temperatureAmbient_;
  temperatureAmbient_["variable"] = "tempAmbient";
  temperatureAmbient_["value"] = DHTMeasureTemperature;
  serializeJson(temperatureAmbient_, temperatureAmbient);

  /*Ambient Humidity Sensor Data*/
  StaticJsonDocument<300> humidityAmbient_;
  humidityAmbient_["variable"] = "humidAmbient";
  humidityAmbient_["value"] = DHTMeasureHumidity;
  serializeJson(humidityAmbient_, humidityAmbient);

  /*Wall Button Sensor Data*/
  StaticJsonDocument<300> buttonStatus_;
  buttonStatus_["variable"] = "wallButton";
  buttonStatus_["value"] = WallButtonStatus;
  serializeJson(buttonStatus_, buttonStatus);

  /*Battery level*/
  StaticJsonDocument<300> batteryLevel_;
  batteryLevel_["variable"] = "batteryLevel";
  batteryLevel_["value"] = BatteryLevel;
  serializeJson(batteryLevel_, batteryLevel);
}
