void setup() {
  Serial.begin(9600);
  analogReadResolution(12);  //Set the resolution of the ADC to 12 bits
}

void loop() {
  int raw = analogRead(A1); //Read sensor output voltage
  float voltage = raw * (3.3 / 4095.0); //Calculate corresponding voltage value
  float temperatureC = voltage * 100.0; //Calculate temperature value (10mV/C)
  Serial.print("Temp: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  delay(1000);
}
