const int potPin = 1; 

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(potPin); 
  Serial.println(sensorValue);   
  delay(50); 
}
