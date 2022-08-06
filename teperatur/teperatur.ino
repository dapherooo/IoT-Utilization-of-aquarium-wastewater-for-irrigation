#include <OneWire.h>
#include <DallasTemperature.h>
 

 
OneWire oneWire(7);
DallasTemperature sensors(&oneWire);
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  delay(1000);
}
