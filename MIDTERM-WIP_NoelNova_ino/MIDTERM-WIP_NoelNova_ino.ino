const int potPin = A5;       
const int buttonPin = 4;    
const int pwmLedPin = 9;     
const int ledPin = 7; 

int potValue = 0;
int buttonState = 0;
int ledBrightness = 0;

unsigned long previousMillis = 0;
const long interval = 500; // 500ms interval

// LED blink state
bool ledState = false;

// Array 
int brightnessLevels[] = {0, 64, 128, 192, 255};
const int numLevels = 5;

void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(pwmLedPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    unsigned long currentMillis = millis();

    potValue = analogRead(potPin);

    // Map potentiometer value to brightness levels
    ledBrightness = map(potValue, 0, 1023, 0, 255);
    analogWrite(pwmLedPin, ledBrightness);

    // Read button state
    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH && currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        ledState = !ledState; // Toggle LED state
        digitalWrite(ledPin, ledState);
    }

    for (int i = 0; i < numLevels; i++) {
        Serial.print("Level ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(brightnessLevels[i]);
    }
}
