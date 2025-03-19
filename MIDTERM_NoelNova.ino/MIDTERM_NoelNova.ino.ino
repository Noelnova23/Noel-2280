const int potPin = 8;       
const int buttonPin = 4;     
const int pwmLedPin1 = 5;    
const int pwmLedPin2 = 6;    
const int buzzerPin = 9;     

// Variables
int potValue = 0;
int buttonState = 0;
bool ledState = false;
int prevBrightness = 0;

// Timer variables
unsigned long previousMillis = 0;
const long interval = 1000; 

void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(pwmLedPin1, OUTPUT);
    pinMode(pwmLedPin2, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    unsigned long currentMillis = millis();

    // Read button state
     buttonState = digitalRead(buttonPin);
    Serial.print("Button State: ");
    Serial.println(buttonState);

    if (buttonState == HIGH) {
        ledState = true;
    } else {
        ledState = false;
    }

    if (ledState) {
        // Read potentiometer value
        potValue = analogRead(potPin);
        int brightness = map(potValue, 0, 1023, 0, 255);
        
        Serial.print("Potentiometer Value: ");
        Serial.println(potValue);
        Serial.print("LED Brightness: ");
        Serial.println(brightness);
        
        // Update LED brightness
        analogWrite(pwmLedPin1, brightness);
        analogWrite(pwmLedPin2, brightness);
        
        // Play buzzer if brightness changes
        if (brightness != prevBrightness) {
            tone(buzzerPin, 1000, 1000); 
            Serial.println("Buzzer Activated");
        }
        prevBrightness = brightness;
    } else {
        analogWrite(pwmLedPin1, 0);
        analogWrite(pwmLedPin2, 0);
    }
}
