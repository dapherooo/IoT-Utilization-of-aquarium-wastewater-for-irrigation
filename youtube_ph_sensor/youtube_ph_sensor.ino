const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
int buf[10],temp=0;

void setup() 
{
 Serial.begin(9600);
}
 
void loop() 
{
 for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 
 float pHVol=(float)avgValue*3.1/1024/4.3;
 //float phValue = -5.70 * pHVol + 22.8;
 float phValue = -3.0 * pHVol+17.5;
 phValue=14.2-phValue;
 Serial.print("sensor = ");
 Serial.println(phValue);
 delay(1000);
}
