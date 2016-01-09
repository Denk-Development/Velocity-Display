// pinning
#define led1 0
#define led2 1
#define segment1C 2
#define segment1B 3
#define segment1D 4
#define segment1A 5
#define segment2C 6
#define segment2B 7
#define segment2D 8
#define segment2A 9
#define smileyGood 10
#define smileyBad 11
#define photoSensor1 12
#define photoSensor2 13

// distance between photo sensor 1 and 2
float s = 0.15f;

unsigned long millisStart, millisStop;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(segment1C, OUTPUT);
  pinMode(segment1B, OUTPUT);
  pinMode(segment1D, OUTPUT);
  pinMode(segment1A, OUTPUT);
  pinMode(segment2C, OUTPUT);
  pinMode(segment2B, OUTPUT);
  pinMode(segment2D, OUTPUT);
  pinMode(segment2A, OUTPUT);
  pinMode(smileyGood, OUTPUT);
  pinMode(smileyBad, OUTPUT);
  pinMode(photoSensor1, INPUT);
  pinMode(photoSensor2, INPUT); 
}

void loop() {
  while (digitalRead(photoSensor1) == LOW) {} // wait for rising edge
  millisStart = millis();
  while (digitalRead(photoSensor2) == LOW) {} // wait for rising edge of photo sensor 2
  millisStop = millis();
  
  float t = (millisStop - millisStart) / 1000.0f;
  
  float v = s / t;
  v *= 3.6 * 16.0;
  
  showVelocity((byte)v);
  delay(3000);
  showNoVelocity();
  delay(1000);
  showSmiley((byte)v);
  delay(700);
  showNoSmiley();
  delay(500);
  showSmiley((byte)v);
  delay(700);
  showNoSmiley();
  delay(500);
  showSmiley((byte)v);
  delay(700);
  showNoSmiley();
  
  delay(1000);
}

void showVelocity(byte velocity) {
  byte segment2 = velocity % 10;
  byte segment1 = velocity % 100 / 10;
  byte segment0 = (byte)(velocity >= 100);
  
  showSegment(0, segment0);
  showSegment(1, segment1);
  showSegment(2, segment2);
}

void showSegment(byte segment, byte value) {
  byte A = (value >> 0) & 1;
  byte B = (value >> 1) & 1;
  byte C = (value >> 2) & 1;
  byte D = (value >> 3) & 1;
  
  switch(segment) {
    case 0:
      // either 0 or 1
      digitalWrite(led1, value);
      digitalWrite(led2, value);
      break;
    case 1:
      digitalWrite(segment1A, A);
      digitalWrite(segment1B, B);
      digitalWrite(segment1C, C);
      digitalWrite(segment1D, D);
      break;
    case 2:
      digitalWrite(segment2A, A);
      digitalWrite(segment2B, B);
      digitalWrite(segment2C, C);
      digitalWrite(segment2D, D);
      break;
  }
}

void showSmiley(byte v) {
  if (v <= 50) {
    digitalWrite(smileyGood, HIGH);
  }
  else {
    digitalWrite(smileyBad, HIGH);
  }
}

void showNoVelocity() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(segment1A, HIGH);
  digitalWrite(segment1B, HIGH);
  digitalWrite(segment1C, HIGH);
  digitalWrite(segment1D, HIGH);
  digitalWrite(segment2A, HIGH);
  digitalWrite(segment2B, HIGH);
  digitalWrite(segment2C, HIGH);
  digitalWrite(segment2D, HIGH);
}

void showNoSmiley() { 
  digitalWrite(smileyGood, LOW);
  digitalWrite(smileyBad, LOW);
}
