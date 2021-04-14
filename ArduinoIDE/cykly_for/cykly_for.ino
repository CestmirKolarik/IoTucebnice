  int prodleva = 100; //prodleva bude 0,1 s  

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sériová komunikace funguje");
}

void loop() {

  //10× vypsat Ahoj
  for(int i = 0; i <10; i++)
  {
    Serial.println("Ahoj");
    delay(prodleva);
  }

  Serial.println("KONEC");
  delay(5000);
  
}
