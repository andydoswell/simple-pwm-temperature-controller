/* PWM fan speed controller
   Copyright A.G.Doswell July 2018
   Visit Andydoz.blogspot.com for description and circuit.
*/


#include <OneWire.h> // from http://playground.arduino.cc/Learning/OneWire
#include <DallasTemperature.h> // from http://www.hacktronics.com/code/DallasTemperature.zip. When adding this to your IDE, ensure the .h and .cpp files are in the top directory of the library.
#define ONE_WIRE_BUS 8 // Data wire from temp sensor is plugged into pin 8 on the Arduino
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

// define constants & global variables
#define fanPin 3 //defines pin the fan driver circuitry is connected to. 
#define setPoint 30 // temperature set point
float tempC; // Temperature in degrees C
int pwm = 0;// pwm for fan control

void setup()
{
  pinMode (fanPin, OUTPUT); // sets our fan pin
  analogWrite (fanPin, 0); // sets the fan off for default condition.
  sensors.begin(); // start up the Dallas temperature sensors
}

void loop()
{
  sensors.requestTemperatures(); // Request temperature
  tempC = sensors.getTempCByIndex(0); // set the temperature in degrees C from the first sensor in line, rather than by address.
  if (tempC != setPoint) { // if the temperature does not equal the setpoint, change the fan speed.
    pwm = pwm + (tempC - setPoint);
    pwm = constrain (pwm, 0, 255);
    analogWrite (fanPin, pwm); // set fan speed
  }
}

