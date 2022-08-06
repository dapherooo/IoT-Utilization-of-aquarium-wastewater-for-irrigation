#include <SoftwareSerial.h>

//RX pin 2, TX pin 3
SoftwareSerial esp8266(2, 3);

#define DEBUG true

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendData("AT\r\n", 2000, DEBUG);
  delay(1000);
  Serial.println("Firmware version:");
  delay(3000);
  sendData("AT+GMR\r\n", 2000, DEBUG);
  Serial.println("** End **");
}

void loop() {}

String sendData(String command, const int timeout, boolean debug) {
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
