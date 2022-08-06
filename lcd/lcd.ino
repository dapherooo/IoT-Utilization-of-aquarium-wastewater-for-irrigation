#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

char auth[] = "2jkuXfLvPRj-7YSHp9I3Qw6ZhmN3Xqgt";
char ssid[] = "POJOK SENJA";
char pass[] = "ciumdulu";
 
float ph_air;
float ph_tan;
float hum;
float suhu;
int sensorValue = 0; 
int pomp1pin1 = 11;
int pomp1pin2 = 10;
int pomp2pin1 = 9;
int pomp2pin2 = 8;    

#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3); // RX, TX

ESP8266 wifi(&Serial1);   
OneWire oneWire(7);
DallasTemperature sensors(&oneWire);
      
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(10);
  lcd.init();                      
  lcd.backlight();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(pomp1pin1, OUTPUT);
  pinMode(pomp1pin2, OUTPUT);
  pinMode(pomp2pin1, OUTPUT);
  pinMode(pomp2pin2, OUTPUT);
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080);
}


void loop()
{
  humidity();
  phtan();
  phair();
  suh();
  lc();
  jalan();
  displayInfo();
  Blynk.run(); 
}
void displayInfo()
{
    Blynk.virtualWrite(V1, String(suhu));
    Blynk.virtualWrite(V2, String(ph_air));
    Blynk.virtualWrite(V3, String(hum));
    Blynk.virtualWrite(V4, String(ph_tan));

}
void jalan(){
  if ( ( suhu == 0 ) && ( ph_air == 0 )){
    pompa1();
  }
  else if ( ( hum == 20 ) && ( ph_tan == 7 )){
    pompa2();
  }
  else{
  digitalWrite(pomp1pin1, LOW);
  digitalWrite(pomp1pin2, HIGH);
  digitalWrite(pomp2pin1, LOW);
  digitalWrite(pomp2pin2, HIGH);
  delay(1000);
  }
}
void pompa1(){
  digitalWrite(pomp1pin1, HIGH);
  digitalWrite(pomp1pin2, LOW);
  delay(10000);
  digitalWrite(pomp1pin1, LOW);
  digitalWrite(pomp1pin2, HIGH);
}

void pompa2(){
  digitalWrite(pomp2pin1, HIGH);
  digitalWrite(pomp2pin2, LOW);
  delay(10000);
  digitalWrite(pomp2pin1, LOW);
  digitalWrite(pomp2pin2, HIGH);
}
void lc(){
  lcd.setCursor(0,0);
  lcd.print("H=");
  lcd.setCursor(2,0);
  lcd.print(hum);
  lcd.setCursor(8,0);
  lcd.print("PHT=");
  lcd.setCursor(12,0);
  lcd.print( ph_tan);
  lcd.setCursor(0,1);
  lcd.print("S=");
  lcd.setCursor(2,1);
  lcd.print(suhu);
  lcd.setCursor(8,1);
  lcd.print("PHA=");
  lcd.setCursor(12,1);
  lcd.print(ph_air);
}

void humidity(){
  hum = (100 - (analogRead(A0) * 0.09765));
  delay(1000);
}

void phtan(){
  sensorValue = analogRead(A2);
   ph_tan = (-0.0693*sensorValue)+7.3855;
   delay(1000);
}

void suh() {
  sensors.requestTemperatures();
  suhu = sensors.getTempCByIndex(0);
  delay(1000);
}

void phair() {
 for(int i=0;i<10;i++) 
    { 
      buffer_arr[i]=analogRead(A1);
      delay(30);
    }
 for(int i=0;i<9;i++)
    {
      for(int j=i+1;j<10;j++)
      {
        if(buffer_arr[i]>buffer_arr[j])
          {
            temp=buffer_arr[i];
            buffer_arr[i]=buffer_arr[j];
             buffer_arr[j]=temp;
           }
        }
      }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*4.6/1024/6; 
 ph_air = -5.70 * volt + calibration_value;
 delay(1000);
}
