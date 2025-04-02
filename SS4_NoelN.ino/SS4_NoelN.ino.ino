const int buttons[] = {18, 19, 21, 22}; // Button GPIOs
const int leds[] = {23, 5, 4, 2};      // LED GPIOs
int buttonStates[4] = {0, 0, 0, 0};

void setup() {
    Serial.begin(115200);
    for (int i = 0; i < 4; i++) {
        pinMode(buttons[i], INPUT_PULLUP); 
        pinMode(leds[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < 4; i++) {
        buttonStates[i] = digitalRead(buttons[i]) == LOW ? 1 : 0; // Active LOW
        digitalWrite(leds[i], buttonStates[i]); // Light up LED when button is pressed
    }

    // Send button states via Serial (e.g., "0,1,0,1")
    Serial.print(buttonStates[0]);
    Serial.print(",");
    Serial.print(buttonStates[1]);
    Serial.print(",");
    Serial.print(buttonStates[2]);
    Serial.print(",");
    Serial.println(buttonStates[3]);

    delay(100);
}