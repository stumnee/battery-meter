#include "SevSeg.h"
SevSeg sevseg;

void setup() {
  Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  pinMode(1, INPUT);

}

int readings[4][10];
int readingPtr = 0;
int sampleSize = 10;
int analong_volt_ins[] = {A0, A1, A2, A3};
int current = 0;
int i = 0;


void loop() {
  int buttonState = digitalRead(1);
  if (buttonState == HIGH) {
    current++;
  }

  // Serial.println(current);

  for (int i = 0; i < 4; i++) {
    readings[i][readingPtr] = analogRead(analong_volt_ins[i]);
  }
  readingPtr = (readingPtr + 1) % sampleSize;
  int total = 0;
  for (int i = 0; i < sampleSize; i++) {
    total += readings[0][i];
  }
  float val = round(500.0 * total / sampleSize / 1024.0 );
  sevseg.setNumberF(val / 100, 2);

  
  sevseg.refreshDisplay(); // Must run repeatedly
}
