#include <Arduino.h>
//--------------------------------------------------------------------
// Author:                Aamir Hasan Khan
// Description:           Pyrometer Temperature Measurements
// Last Revision Date:    02-10-2019
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Arduino Libraries
#include <DallasTemperature.h>
#include <OneWire.h>
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Arduino pin numbers
#define Signal_PIN 2
#define Voltage_PIN A0
#define Current_PIN A1
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Libraries configuration
OneWire oneWire(Signal_PIN);
DallasTemperature sensors(&oneWire);
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Program Variables
float OC_Voltage;
float SC_Current = 1.23;
float temperature = 32;
float irradiance_G;
float g[5];
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// The setup function runs once when you press reset
void setup()
{

  // serial output initialization
  Serial.begin(9600);
  // sensor will be initialized
  //sensors.begin();
}
//--------------------------------------------------------------------

void clac_irradiance(float i, float t)
{

  g[0] = 816.5 * i;
  g[1] = 0.5544 * i * i;
  g[2] = 0.00103 * i * i * i;
  g[3] = 0.0001957 * i * t * t;
  g[4] = 0.4104 * t * i;
  g[5] = 0.000534 * i * i * t;
}

//--------------------------------------------------------------------
// The loop function runs over and over again forever.
void loop()
{

  Serial.print("Temperature : ");
  Serial.println(temperature);
  Serial.print("Current : ");
  Serial.println(SC_Current);

  clac_irradiance(SC_Current, temperature);

  irradiance_G = g[0] + g[1] + g[2] + g[3] - g[4] - g[5];

  for (int i = 0; i <= 5; i++)
  {
    Serial.println(g[i]);
  }
  Serial.print("irradiance : ");
  Serial.println(irradiance_G);
  delay(5000); // 1s break till next measurment
}
//--------------------------------------------------------------------