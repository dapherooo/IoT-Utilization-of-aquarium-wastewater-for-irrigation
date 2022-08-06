int pomp1pin1 = 11;
int pomp1pin2 = 10;
int pomp2pin1 = 9;
int pomp2pin2 = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(pomp1pin1, OUTPUT);
  pinMode(pomp1pin2, OUTPUT);
  pinMode(pomp2pin1, OUTPUT);
  pinMode(pomp2pin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:   
  digitalWrite(pomp1pin1, HIGH);
  digitalWrite(pomp1pin2, LOW);

  digitalWrite(pomp2pin1, HIGH);
  digitalWrite(pomp2pin2, LOW);
  delay(1000);

  digitalWrite(pomp1pin1, LOW);
  digitalWrite(pomp1pin2, HIGH);

  digitalWrite(pomp2pin1, LOW);
  digitalWrite(pomp2pin2, HIGH);
  delay(1000);
}
