//info//
//DHT11 Temperature & Humidity Sensor


//setup//
// REQUIRES the following Arduino libraries:
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

//Download and install the Adafruit Unified Sensor library manually from GitHub, or alternatively, install it within the Arduino IDE itself 
//(By the way, I cound't find them in Arduino IDE) 
//Open the library manager. Tools > Manage Libraries > Search for “Adafruit Unified Sensor”. Then, click Install. If you couldn't find it, try to install "Adafruit 10DOF" instead of. It might ask you if you like to download all missing dependencies, click install all. 
//Open the library manager in Arduino IDE. Tools > Manage Libraries > Search for “DHT Sensor”. Then, click Install. If you coundn't find it, try to install "DHT sensor library" instead of it

//In case if you couldn't find any libraries can use in Arduino IDE follow the step below to include the libraries to the code
//Click the link to download the library https://github.com/adafruit/Adafruit_Sensor
//Click the link to download the library https://github.com/adafruit/DHT-sensor-library
//Include the both libraries. Sketch > Include Library > Add .Zip Library

//pinout: VCC, GND, DATA
//connect the sensor's VCC pin to the Arduino's VCC pin
//connect the sensor's GND pin to the Arduino's GND pin
//connect the sensor's DATA pin to the Arduino's pin 0
//connect Arduino MKR wifi 1010 to PC through a USB cable
//upload the code to Arduino MKR Wifi 1010
//open Serial Monitor (Tools -> Serial Monitor)


//function//
//The value of temperature and hummidity will be displayed on the Serial Monitor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 0     // Digital pin connected to the DHT sensor 

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE); //create object dht for the DHT_Unified class

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
 
  sensor_t sensor;//object for sensor_t class
  dht.temperature().getSensor(&sensor);//Fills the sensor structure with metadata about the temperature
  dht.humidity().getSensor(&sensor);//Fills the sensor structure with metadata about the humudity
  
  // Set delay between sensor readings based on sensor details
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;// Create an event to store the data read from the sensor
  dht.temperature().getEvent(&event);//fills the event structure with the latest temperature reading
  // Check if the temperature reading is valid
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  //print the value of temperature
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);//fills the event structure with the latest humidity reading
  // Check if the temperature reading is valid
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  //print the value of humidity
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
