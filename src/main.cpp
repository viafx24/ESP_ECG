
#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include "MAX30105.h"

// Wifi

const char *ssid = "SFR_EC58";
//const char *password = "uguele2vocuminhonext";// parents
const char *password = "96wwza4yfz24qhtc4mxq"; // hameau

unsigned long Time;
String Data_wifi;

// to set the static IP address to 192, 168, 1, 184
IPAddress local_IP(192, 168, 1, 70);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

MAX30105 particleSensor;

int Wire_Not_Plugged=2000;

void setup()
{

  pinMode(35, INPUT); // Setup for leads off detection LO +
  pinMode(32, INPUT); // Setup for leads off detection LO -
  pinMode(34, INPUT);

  // initialize the serial communication:
  Serial.begin(9600);
  delay(2000);

  if (!WiFi.config(local_IP, gateway, subnet))
  {
    Serial.println("IP adress could not be set to 192.168.1.70");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected");
  server.begin();


  // Initialize sensor
  if (particleSensor.begin() == false)
  {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive

}

void loop()
{

  WiFiClient client = server.available(); // listen for incoming clients

  if (client)
  { // if you get a client,
    // Serial.println("New Client."); // print a message out the serial port
    String currentLine = "";

    while (client.connected())
    { // loop while the client's connected

      if ((digitalRead(35) == 1) || (digitalRead(32) == 1))
      {
        Serial.println(Wire_Not_Plugged);
        client.println(Wire_Not_Plugged);
      }
      else
      {
        // send the value of analog input 0:
        //  Serial.println(analogRead(34));
        //Time = millis();
        Data_wifi = String(String(millis()) + "," + String(particleSensor.getRed()) + "," + String(particleSensor.getIR()) + "," + String(analogRead(34)));
        client.println(Data_wifi);
      }
      //Wait for a bit to keep serial data from saturating
      delay(0.1);
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}



/*
  MAX30105 Breakout: Output all the raw Red/IR/Green readings
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  Outputs all Red/IR/Green values.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
*/






#define debug Serial //Uncomment this line if you're using an Uno or ESP
//#define debug SerialUSB //Uncomment this line if you're using a SAMD21

void setup()
{
  debug.begin(9600);
  debug.println("MAX30102 Basic Readings Example");


}

void loop()
{
//  debug.print(" R[");
//  debug.print(particleSensor.getRed());
//  debug.print("] IR[");
//  debug.print(particleSensor.getIR());
//  debug.print("]");
//  debug.println(); 




}