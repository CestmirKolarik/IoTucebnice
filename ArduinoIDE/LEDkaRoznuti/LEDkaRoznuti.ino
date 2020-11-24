  #define cervena 5
  /* je možné použít jakýkoliv z těchto zápisů
  #define modra D1;
  const char modra = 5;
  char modra 5;
  int modra = D1;
  const char modra = 5;
  */


void setup() {
  pinMode(cervena,OUTPUT);

}

void loop() {
  digitalWrite(cervena, HIGH);
  delay();
  digitalWrite(cervena, LOW);
  delay();

}
