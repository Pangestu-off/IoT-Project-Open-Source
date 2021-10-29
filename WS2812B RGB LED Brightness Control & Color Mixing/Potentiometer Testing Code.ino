int Pot = A0;
int PotVal = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  PotVal = analogRead(Pot); 
  Serial.println(PotVal);
}
