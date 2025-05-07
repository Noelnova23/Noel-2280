const int buttonNext = 2;
const int buttonPrev = 3;
const int potPin = A0;
const int ledPins[3] = {8, 9, 10};

void setup() {
  pinMode(buttonNext, INPUT_PULLUP);
  pinMode(buttonPrev, INPUT_PULLUP);
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  int nextState = digitalRead(buttonNext);
  int prevState = digitalRead(buttonPrev);
  int potValue = analogRead(potPin); // 0 - 1023

  // Send control data
  Serial.print(nextState == LOW ? "N" : ""); // Next song
  Serial.print(prevState == LOW ? "P" : ""); // Previous song
  Serial.print("V");
  Serial.print(potValue); // Volume

  // Send LED random pattern
  Serial.print("L");
  for (int i = 0; i < 3; i++) {
    int ledState = random(0, 2);
    digitalWrite(ledPins[i], ledState);
    Serial.print(ledState);
  }
  Serial.println();

  delay(200); // Small delay to avoid flooding serial
}