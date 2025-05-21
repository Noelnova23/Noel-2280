const int potPin = 6; 
const int ledPins[3] = {8, 9, 10};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(115200);
  delay(1000); // Wait for Processing to be ready
  randomSeed(analogRead(0));
}

void loop() {
  int potValue = analogRead(potPin); // 0 - 1023

  // Send volume and LED data
  Serial.print("V");
  Serial.print(potValue);

  Serial.print("L");
  for (int i = 0; i < 3; i++) {
    int ledState = random(0, 2);
    digitalWrite(ledPins[i], ledState);
    Serial.print(ledState);
  }
 
  Serial.println();
  delay(200);
}