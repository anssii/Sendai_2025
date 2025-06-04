#define BLYNK_TEMPLATE_ID "zzz"
#define BLYNK_TEMPLATE_NAME "yyy"
#define BLYNK_AUTH_TOKEN "xxx"

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char ssid[] = "aterm-00e444-g";
char pass[] = "989f4ca2bc85b";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

