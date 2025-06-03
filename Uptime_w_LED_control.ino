#define BLYNK_TEMPLATE_ID "TMPL6BPwhWWbe"
#define BLYNK_TEMPLATE_NAME "my first template"
#define BLYNK_AUTH_TOKEN "qzQxb81_QBAr_q2tkBGkUgaBoW5gpPgE"

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
BLYNK_WRITE(V1)  // This function is triggered when Virtual Pin V1 changes
{
  int value = param.asInt();  // Get the value from the Blynk app (0 or 1)
  digitalWrite(LED_BUILTIN, value);  // Set the LED pin to HIGH or LOW
}
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  // Ensure LED is OFF initially
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}
void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

