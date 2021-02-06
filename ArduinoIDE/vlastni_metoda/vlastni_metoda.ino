  #define cervena 5 //D1
  int prodleva = 1000;

void setup() {
  pinMode(cervena, OUTPUT);

  blikni();

}

void loop() {

}

void blikni() {
  digitalWrite(cervena, HIGH);
  delay(prodleva);
  digitalWrite(cervena, LOW);
  delay(prodleva);

}
