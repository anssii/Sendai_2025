#define BLYNK_TEMPLATE_ID "zzz"
#define BLYNK_TEMPLATE_NAME "yyy"
#define BLYNK_AUTH_TOKEN "xxx"

#include <SPI.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include <BlynkSimpleWiFiNINA.h>

char ssid[] = "aterm-00e444-g";
char pass[] = "989f4ca2bc85b";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}
//Control for RED color
BLYNK_WRITE(V4)  // This function is triggered when Virtual Pin V1 changes
{
  int value = param.asInt();  // Get the value from the Blynk app (0 or 1)
  WiFiDrv::analogWrite(25, value);
}

void setup()
{
  WiFiDrv::pinMode(25, OUTPUT); //define green pin
  WiFiDrv::pinMode(26, OUTPUT); //define red pin
  WiFiDrv::pinMode(27, OUTPUT); //define blue pin

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

