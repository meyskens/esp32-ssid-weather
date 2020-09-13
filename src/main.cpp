#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println();
  Serial.println("Configuring access point...");


  if (!bmp.begin(0x76))
  {
    Serial.println("Could not find a valid BMP280 sensor");
    while (true)
    {
    }
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  String suffix = "";

  suffix += String(bmp.readTemperature());
  suffix += "°C ";

  suffix += String(bmp.readPressure() / 100);
  suffix += " hPa";

  String ssid = "#ITFactory " + suffix;
  WiFi.softAP(ssid.c_str());

  Serial.println("AP online!");
  digitalWrite(LED_BUILTIN, LOW);
  delay(10000);
}