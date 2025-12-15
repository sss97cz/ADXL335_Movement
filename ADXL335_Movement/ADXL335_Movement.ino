// ADXL335 – Print movement direction over Serial
// Auto-calibrates on startup

const int xPin = A0;
const int yPin = A1;
const int zPin = A2;

int xOffset = 0;
int yOffset = 0;
int zOffset = 0;

// Adjust sensitivity here if needed
const int deadZone  = 20;
const int threshold = 20;

void setup() {
  Serial.begin(9600);
  calibrate();

  Serial.println("Ready. Tilt the accelerometer.");
}

void loop() {
  int x = analogRead(xPin) - xOffset;
  int y = analogRead(yPin) - yOffset;
  int z = analogRead(zPin) - zOffset;

  Serial.println(String(x) +", "+ String(y)+ ", " + String(z));

  // Ignore small noise
  if (abs(x) < deadZone && abs(y) < deadZone) {
    Serial.println("FLAT");
  } 
  else if (x > threshold) {
    Serial.println("RIGHT");
  } 
  else if (x < -threshold) {
    Serial.println("LEFT");
  } 
  else if (y > threshold) {
    Serial.println("FORWARD");
  } 
  else if (y < -threshold) {
    Serial.println("BACKWARD");
  }

  delay(200);
}

void calibrate() {
  long xSum = 0;
  long ySum = 0;
  long zSum = 0;

  Serial.println("Calibrating... keep the board flat.");

  for (int i = 0; i < 200; i++) {
    xSum += analogRead(xPin);
    ySum += analogRead(yPin);
    zSum += analogRead(zPin);
    delay(5);
  }

  xOffset = xSum / 200;
  yOffset = ySum / 200;
  zOffset = zSum / 200;

  Serial.println("Calibration done.");
}
