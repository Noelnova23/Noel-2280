import processing.serial.*;
Serial myPort;
int[] sequence = new int[4];  
int sequenceIndex = 0;       
int userIndex = 0;            
boolean userTurn = false;     
int[] userInput = new int[4];  
color[] colors = {color(255, 0, 0), color(0, 255, 0), color(0, 0, 255), color(255, 255, 0)};
int buttonSize = 150;

void setup() {
    size(600, 600);
    myPort = new Serial(this, Serial.list()[0], 112500);
    myPort.bufferUntil('\n'); 
    generateSequence();
}

void draw() {
    background(50);
    
    // Display Simon buttons
    for (int i = 0; i < 4; i++) {
        fill(colors[i]);
        rect((i % 2) * 300, (i / 2) * 300, buttonSize, buttonSize);
    }

    // Show current sequence
    if (!userTurn) {
        showSequence();
    }
}

void generateSequence() {
    for (int i = 0; i < 4; i++) {
        sequence[i] = int(random(4)); // Randomly choose 0-3
    }
    userIndex = 0;
    userTurn = false;
}

void showSequence() {
    for (int i = 0; i <= sequenceIndex; i++) {
        fill(colors[sequence[i]]);
        rect((sequence[i] % 2) * 300, (sequence[i] / 2) * 300, buttonSize, buttonSize);
        delay(500);
        background(50);
        delay(300);
    }
    userTurn = true;
}

void serialEvent(Serial p) {
    String data = p.readStringUntil('\n');
    if (data != null) {
        data = trim(data);
        String[] parts = split(data, ",");
        for (int i = 0; i < 4; i++) {
            userInput[i] = int(parts[i]);
        }
