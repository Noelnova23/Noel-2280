const int LED1 = 1; //13
const int LED2 = 2; //12
const int LED3 = 3; //11
const int LED4 = 4; //10

// Declare variables
int pattern = 0;      // Controls the LED pattern
int brightness = 255;
int speed = 500;      // Delay time in milliseconds

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  if (pattern >= 4) {
    pattern = 0; // Reset pattern after 4 cycles
  }

  if (pattern == 0) {
    // Pattern 1: Sequential Blink
    digitalWrite(LED1, HIGH);
    delay(speed);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(speed);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    delay(speed);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    delay(speed);
    digitalWrite(LED4, LOW);
  } 
  else if (pattern == 1) {
    // Pattern 2: Alternating Blink
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, HIGH);
    delay(speed);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED4, HIGH);
    delay(speed);
    digitalWrite(LED2, LOW);
    digitalWrite(LED4, LOW);
  } 
  else if (pattern == 2) {
    // Pattern 3: All Blink Together
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(speed);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(speed);
  } 
  else {
    // Pattern 4: Knight Rider Style
    for (int i = 4; i <= 1; i++) {
      digitalWrite(i, HIGH);
      delay(speed / 2);
      digitalWrite(i, LOW);
    }
    for (int i = 4; i >= 2; i--) {
      digitalWrite(i, HIGH);
      delay(speed / 2);
      digitalWrite(i, LOW);
    }
  }

  pattern++; // Move to the next pattern
  delay(speed); // General delay before next pattern cycle
}