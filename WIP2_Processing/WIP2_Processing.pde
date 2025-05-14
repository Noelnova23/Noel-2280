import ddf.minim.*;
import processing.serial.*;

Minim minim;
AudioPlayer[] songs;
int currentSong = 0;
float volume = 0.5;

Serial myPort;

void setup() {
  size(600, 400);
  background(0);

  // Serial setup
  printArray(Serial.list()); // Check port list
  myPort = new Serial(this, Serial.list()[0], 9600); // Select correct port
  myPort.bufferUntil('\n');

  // Load songs
  minim = new Minim(this);
  songs = new AudioPlayer[] {
    minim.loadFile("MP3/dokkan1.mp3"),
    minim.loadFile("MP3/dokkan2.mp3"),
    minim.loadFile("MP3/dokkan3.mp3"),
  };
  songs[currentSong].loop();
}

void draw() {
  // Basic LED visuals
  background(0);
  fill(255, 0, 0);
  ellipse(150, 200, 100, 100);
  fill(0, 255, 0);
  ellipse(300, 200, 100, 100);
  fill(0, 0, 255);
  ellipse(450, 200, 100, 100);
}

void serialEvent(Serial port) {
  String data = port.readStringUntil('\n');
  if (data == null) return;

  data = data.trim();

  if (data.contains("N")) {
    changeSong(1);
  }
  if (data.contains("P")) {
    changeSong(-1);
  }

  int vIndex = data.indexOf("V");
  int lIndex = data.indexOf("L");
  if (vIndex != -1 && lIndex != -1) {
    String volString = data.substring(vIndex + 1, lIndex);
    int volVal = int(volString);
    volume = map(volVal, 0, 1023, 0, 1);
    songs[currentSong].setGain(map(volume, 0, 1, -30, 0)); // Set volume
  }

  if (lIndex != -1 && data.length() >= lIndex + 4) {
    String leds = data.substring(lIndex + 1, lIndex + 4);
    updateLEDVisuals(leds);
  }
}

void changeSong(int dir) {
  songs[currentSong].pause();
  currentSong = (currentSong + dir + songs.length) % songs.length;
  songs[currentSong].rewind();
  songs[currentSong].loop();
}

void updateLEDVisuals(String pattern) {
  for (int i = 0; i < 3; i++) {
    if (pattern.charAt(i) == '1') {
      fill(i == 0 ? color(255, 0, 0) : i == 1 ? color(0, 255, 0) : color(0, 0, 255));
    } else {
      fill(50);
    }
    ellipse(150 + 150 * i, 200, 100, 100);
  }
}
