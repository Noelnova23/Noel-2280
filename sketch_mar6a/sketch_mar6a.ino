vconst int LED1 = 1;  
const int LED2 = 2;  
const int LED3 = 3;  
const int LED4 = 4;  
const int buttonPin = 5; 

// Declare variables
int pattern = 0;       // Controls the LED pattern
int speed = 500;       // Delay time in milliseconds
int buttonState = 0;   // Store button state
int lastButtonState = 0; // Store previous button state for debounce

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Set button as input with internal pull-up resistor
}

void loop() {
  // Read button state
  buttonState = digitalRead(buttonPin);

  // Detect button press (falling edge detection)
  if (buttonState == LOW && lastButtonState == HIGH) {
    pattern++;  // Move to the next pattern
    if (pattern >= 4) {
      pattern = 0; // Reset to the first pattern
    }
    delay(200); // Debounce delay to avoid multiple triggers
  }

  lastButtonState = buttonState; // Update last button state

  // Display different patterns based on the counter
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
    for (int i = 1; i <= 4; i++) {
      digitalWrite(i, HIGH);
      delay(speed / 2);
      digitalWrite(i, LOW);
    }
    for (int i = 3; i >= 2; i--) {
      digitalWrite(i, HIGH);
      delay(speed / 2);
      digitalWrite(i, LOW);
    }
  }
}