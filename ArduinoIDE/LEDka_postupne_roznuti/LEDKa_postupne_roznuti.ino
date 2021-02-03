  #define red 12 //D6
  #define gre 13 //D7
  #define blu 15 //D8

  int prodleva = 1500; //prodleva sekunda a půl

void setup() {

  pinMode(red, OUTPUT);
  pinMode(gre, OUTPUT);
  pinMode(blu, OUTPUT);
}

void loop() {

  //červená - #FF0000 - (255, 0, 0)
  digitalWrite(red, HIGH);
  digitalWrite(gre, LOW);
  digitalWrite(blu, LOW);
  delay(prodleva);

  //žlutá - #FFFF00 - (255, 255, 0)
  digitalWrite(red, HIGH);
  digitalWrite(gre, HIGH);
  digitalWrite(blu, LOW);
  delay(prodleva);

}
