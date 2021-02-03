  #define red 15 //D8
  #define gre 13 //D7
  #define blu 12 //D6

  int prodleva = 1500; //prodleva sekunda a půl

void setup() {

  pinMode(red, OUTPUT);
  pinMode(gre, OUTPUT);
  pinMode(blu, OUTPUT);
}

void loop() {

  //červená - #8b00ff - (139; 0; 255)
  analogWrite(red,556);
  analogWrite(gre, 0);
  analogWrite(blu, 1020);
  delay(prodleva);

}
