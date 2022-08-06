//tes sensor pH tanah 

/*
wiring:
kabel putih -> GND
kabel hitam -> output to A0
*/

//analog pin 
#define analogInPin A0  //sambungkan kabel hitam (output) ke pin A0

//variable
int sensorValue = 0;        //ADC value from sensor
float outputValue = 0.0;        //pH value after conversion

void setup() {
  //initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  //read the analog in value:
  sensorValue = analogRead(analogInPin);

  //Mathematical conversion from ADC to pH
  //rumus didapat berdasarkan datasheet 
  outputValue = (-0.0693*sensorValue)+7.3855;

  //print the results to the serial monitor:
  Serial.print("sensor ADC= ");
  Serial.print(sensorValue);
  Serial.print("  output Ph= ");
  Serial.println(outputValue);

  delay(1000);
}
