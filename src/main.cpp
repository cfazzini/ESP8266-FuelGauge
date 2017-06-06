/*************

Code copied from


*******************/
#include <Arduino.h>
#include <WiFiManager.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";
;
// Turn OFF temperature compensation if FIXEDSPEED == 1
#define FIXEDSPEED 1


// set HC-SR04 Pins
int pingPin = 13;
//Hello
int inPin = 14;

// ESP8266 DEEP_SLEEP interval = 5m
int sleepInterval = 500;
WiFiManager wifiManager;



/*
  This function converts microseconds to centimeters
*/
float microsecondsToCentimeters(long microseconds, float c) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // actually 29 microsec/cm = 10000/29 = 344.8 m/s, ie 22.3 deg C
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds * c / 20000;
}

/*
  This function returns the distance to the object
  in front of the HC-SR04 sensor with Temperature
  compensation depending of FIXEDSPEED setting
*/
float getDistance(float pi_temp) {
  long duration;
  float c; // speed of sound

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  // estimate speed of sound from temperature:

  if (FIXEDSPEED == 1)  {
    c = 10000.0 / 29; // Original value for c in code
  }  else {
    c = 331.3 + 0.606 * pi_temp / 100;
  }

  return microsecondsToCentimeters(duration, c);
}

float getFuelLevel (float distance) {



}
void setupWifi() {
  wifiManager.autoConnect("FuelGauge-AutoConnectAP");
  Serial.println("connected...yeey :)");
}


void setup (void){
  setupWifi();
  ESP.deepSleep(1000000 * sleepInterval);
}


void loop (){


}
