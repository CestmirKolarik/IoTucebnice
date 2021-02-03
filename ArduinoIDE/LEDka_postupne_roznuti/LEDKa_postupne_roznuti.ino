  #define ledka 5 //D1

void setup() {

  pinMode(ledka, OUTPUT);
}

void loop() {

for(int i = 0; i < 1024; i++)
  {
    analogWrite(ledka, i);
    delay(5);
  }
}
