  #define cervena 5 //D1
  int prodleva = 1000;

void setup() {
  pinMode(cervena, OUTPUT);
  blikni(6);
}

void loop() {

}

void blikni(int pocet) {
  for(int i = 0; i < pocet; i++)
  {
    digitalWrite(cervena, HIGH);
    delay(prodleva);
    digitalWrite(cervena, LOW);
    delay(prodleva);
  }
}
