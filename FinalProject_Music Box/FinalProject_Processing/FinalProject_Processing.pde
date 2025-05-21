import ddf.minim.*;
import processing.serial.*;

Minim minim;
AudioPlayer[] songs;
int currentSong = 0;
float volume = 0.5;

Serial myPort;

String ledPattern = "000"; // still used, but not visualized anymore

void setup() {
  size(600, 400);
  background(0);

  // Serial setup
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 115200);
  myPort.bufferUntil('\n');

  // Load songs
  minim = new Minim(this);
  songs = new AudioPlayer[] {
    minim.loadFile("MP3/dokkan2.mp3"),
    minim.loadFile("MP3/dokkan1.mp3"),
    minim.loadFile("MP3/dokkan3.mp3"),
  };
  songs[currentSong].loop();
}

void draw() {
  background(0);

  // Draw fixed ellipses for control (not tied to LED pattern)
  fill(255, 0, 0);   // Red - Previous
  ellipse(150, 200, 100, 100);

  fill(255, 255, 0); // Yellow - Stop
  ellipse(300, 200, 100, 100);

  fill(0, 0, 255);   // Blue - Next
  ellipse(450, 200, 100, 100);

  // Labels
  fill(255);
  textAlign(CENTER);
  textSize(16);
  text("Previous", 150, 320);
  text("Stop",     300, 320);
  text("Next",     450, 320);
}

void serialEvent(Serial port) {
  String data = port.readStringUntil('\n');
  if (data == null) return;

  data = data.trim();
  println("Received: " + data);

  int vIndex = data.indexOf("V");
  int lIndex = data.indexOf("L");

  if (vIndex != -1 && lIndex != -1) {
    String volString = data.substring(vIndex + 1, lIndex);
    int volVal = int(volString);
    volume = map(volVal, 0, 1023, 0, 1);
    songs[currentSong].setGain(map(volume, 0, 1, -30, 0));
  }

  if (lIndex != -1 && data.length() >= lIndex + 4) {
    ledPattern = data.substring(lIndex + 1, lIndex + 4);
    // LED pattern is still read but not visualized
  }
}

void mousePressed() {
  if (dist(mouseX, mouseY, 150, 200) < 50) {
    changeSong(-1); // Previous
  } else if (dist(mouseX, mouseY, 300, 200) < 50) {
    stopSong();     // Stop
  } else if (dist(mouseX, mouseY, 450, 200) < 50) {
    changeSong(1);  // Next
  }
}

void changeSong(int dir) {
  songs[currentSong].pause();
  currentSong = (currentSong + dir + songs.length) % songs.length;
  songs[currentSong].rewind();
  songs[currentSong].loop();
}

void stopSong() {
  songs[currentSong].pause();
}
