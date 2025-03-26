import processing.serial.*; 
Serial myPort; 
int sensorValue = 0; 
int winWidth = 800; 
int winHeight = 600; 

void setup() 
{
  size(winWidth, winHeight);
  background(50, 50, 100);
  String portName = Serial.list()[0]; 
  myPort = new Serial(this, portName, 115200);
}

void draw() {
  background(50, 50, 100); 

 
  int shapeSize = map(sensorValue, 0, 1023, 50, 200); 
  int colorVal = map(sensorValue, 0, 1023, 0, 255);  
  int xPos = map(sensorValue, 0, 1023, 100, winWidth - 100); 
 
  // Draw ellipse with dynamic properties
  fill(colorVal, 100, 200);
  ellipse(xPos, winHeight / 4, shapeSize, shapeSize);

  // Draw rectangle with dynamic properties
  fill(200, colorVal, 100);
  rect(winWidth / 2 - 50, winHeight / 2 - 50, shapeSize, shapeSize);

  // Draw line with dynamic color and stroke weight
  stroke(255, 100, colorVal);
  strokeWeight(map(sensorValue, 0, 1023, 1, 10));
  line(100, winHeight - 100, winWidth - 100, 100);
}

void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  if (inString != null) 
  {
    inString = trim(inString);
    sensorValue = int(inString);
  }
}
