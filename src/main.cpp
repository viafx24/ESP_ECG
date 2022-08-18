
#include <Arduino.h>
#include <WiFi.h>

// Wifi

const char *ssid = "SFR_EC58";
//const char *password = "uguele2vocuminhonext";// parents
const char *password = "96wwza4yfz24qhtc4mxq"; // hameau

// to set the static IP address to 192, 168, 1, 184
IPAddress local_IP(192, 168, 1, 70);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

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

  server.begin();
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
        client.println(analogRead(34));
      }
      //Wait for a bit to keep serial data from saturating
      delay(0.5);
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}

  // void setup()
  // {

  //   Serial.begin(9600);
  //   Wire.begin();
  //   delay(2000);

  //   if (!mpu.setup(0x68))
  //   { // change to your own address
  //     while (1)
  //     {
  //       Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
  //       delay(5000);
  //     }
  //   }

  //   if (!WiFi.config(local_IP, gateway, subnet))
  //   {
  //     Serial.println("IP adress could not be set to 192.168.0.20");
  //   }

  //   WiFi.begin(ssid, password);

  //   while (WiFi.status() != WL_CONNECTED)
  //   {
  //     delay(500);
  //     // Serial.print(".");
  //   }

  //   server.begin();

  //   mpu.setAccBias(1013.52, 19.45, 996.83);
  //   mpu.setGyroBias(0.09, 1.55, 4.78);
  //   mpu.setMagBias(113.95, 329.77, -416.71);
  //   mpu.setMagScale(1.09, 0.99, 0.94);
  //   mpu.setMagneticDeclination(2);

  //   mpu.setFilterIterations(10);
  // }

  // void loop()
  // {

  //   WiFiClient client = server.available(); // listen for incoming clients

  //   if (client)
  //   { // if you get a client,
  //     // Serial.println("New Client."); // print a message out the serial port
  //     String currentLine = "";

  //     while (client.connected())
  //     { // loop while the client's connected

  //       if (mpu.update())
  //       {

  //         currentLine = String(millis()) + "," + String(mpu.getAccX()) + "," + String(mpu.getAccY()) + "," + String(mpu.getAccZ()) +
  //                       "," + String(mpu.getGyroX()) + "," + String(mpu.getGyroY()) + "," + String(mpu.getGyroZ()) +
  //                       "," + String(mpu.getMagX()) + "," + String(mpu.getMagY()) + "," + String(mpu.getMagZ()) +
  //                       "," + String(mpu.getRoll()) + "," + String(mpu.getPitch()) + "," + String(mpu.getYaw()) +
  //                       "," + String(mpu.getQuaternionX()) + "," + String(mpu.getQuaternionY()) + "," + String(mpu.getQuaternionZ()) +
  //                       "," + String(mpu.getQuaternionW());

  //         client.println(currentLine);
  //         delay(10);
  //       }
  //     }

  //     client.stop();
  //     Serial.println("Client Disconnected.");
  //   }
  // }