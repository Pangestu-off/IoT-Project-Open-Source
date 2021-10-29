int in1 = 0;
int in2 = 1;
int in3 = 2;
int in4 = 3;

int val = 1;

#define pot A0

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  
  pinMode(pot, INPUT);
}

void loop() {
  val = analogRead(pot) / 200;

  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  delay(val);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(val);

  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  delay(val);
  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  delay(val);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(val);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(val);

  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);
  delay(val);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in4, LOW);
  delay(val);

}
