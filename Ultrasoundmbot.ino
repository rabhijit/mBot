#define TIMEOUT 30000
#define WAITING_TIME 1000
#define ULTRASONIC 12
#define TOO_CLOSE 12

// If you are using PORT 1 of the mCore, the ultrasonic sensor is connected to digital pin 12
// If you are using PORT 2 of the mCore, the ultrasonic sensor is connected to digital pin 10

void setup() {
  Serial.begin(9600);
}

void loop() {
  pinMode(ULTRASONIC, OUTPUT);

  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, LOW);

  pinMode(ULTRASONIC, INPUT);

  long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
  double distance = ((double)duration * 0.034321) / 2;
  /*
   * Serial.print("Estimated distance: ");
   * Serial.print(distance);
   * Serial.println("centimetres");
  */
  if (distance <= TOO_CLOSE) {
    // stop function here
   //delay(WAITING_TIME);
  }
  if (distance > TOO_CLOSE){
  //move fwd
   //delay(WAITING_TIME);
  }
  delay(WAITING_TIME);
}
