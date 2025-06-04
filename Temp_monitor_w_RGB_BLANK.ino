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
float temp_limit = 30.0; // Default limit in °C

void setup()
{
  Serial.begin(9600);
  analogReadResolution(12); // 12-bit ADC

  // Set RGB LED pins
  WiFiDrv::pinMode(25, OUTPUT); // green
  WiFiDrv::pinMode(26, OUTPUT); // red
  WiFiDrv::pinMode(27, OUTPUT); // blue
  WiFiDrv::analogWrite(27, 0);  // blue off

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent); // Read temperature every second
}

void loop()
{
  Blynk.run();
  timer.run();
}

// Read temp limit (V6)
BLYNK_WRITE(V6)
{
  temp_limit = param.asFloat();  // Get value from slide control as float
  Serial.print("Updated temp_limit: "); //Local debugging, print update to serial
  Serial.println(temp_limit);
}
//Timer event to read temperature and control RGB
void myTimerEvent()
{
  float temp = readTemp();
  // Send temperature to Blynk
  Blynk.virtualWrite(V2, temp);

  // LED logic based on temp_limit
  if (temp < temp_limit) {
    WiFiDrv::analogWrite(26, 255); // green ON
    WiFiDrv::analogWrite(25, 0);   // red OFF
  } else {
    WiFiDrv::analogWrite(26, 0);   // green OFF
    WiFiDrv::analogWrite(25, 255); // red ON
  }
}
//Read temp sensor value and calculate average
float readTemp() {
  long totalRaw = 0;
  for (int i = 0; i < 10; i++) {
    totalRaw += analogRead(A1);
    delay(10);
  }
  float averageRaw = totalRaw / 10.0;
  float voltage = averageRaw * (3.3 / 4095.0);
  float temperatureC = voltage * 100.0;
  return temperatureC;
}
