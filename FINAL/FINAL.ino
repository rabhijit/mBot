//MACROS
#include "stdbool.h"
//Movement Macros
#include <MeMCore.h>
MeDCMotor left(M1);
MeDCMotor right(M2);

//IR & Ultrasonic Macros: 2 Analog pins
//MeDCMotor left(M1);
//MeDCMotor right(M2);
#define CENTERLEFT 0.65
#define CENTERRIGHT 1.9
#define WAITING_TIME 500
#define IRleft A0 //S1
#define IRright A1 //S2
#define TOOCLOSELEFT 2.90
#define TOOCLOSERIGHT -0.5
#define TIMEOUT 300000
#define ULTRASONIC 12
#define TOOCLOSEFRONT 10
#define LS 9      // left sensor
#define RS 10     // right sensor

//Black line Detector Macros: 2 Analog pins
#define IR_down_1 9
#define IR_down_2 10


//Sound Challenge Macros: 2 Analog pins
#define THRESHOLD 1
#define SAMPLENUM 50
#define f_A_pin A3 //300 Hz 
#define f_B_pin A2 //3000 Hz
#define TIME 100
#define MIN_A 30
#define MIN_B 50
#define MINVOL 100 //Min volume to consider it as the sound challenge


//Colour Challenge Macros: 
MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);
MeBuzzer buzzer;
#define RGBdelay 200 // delay before starting measurement to allow LDR to stabilize
#define LDRdelay 50 // delay between each measurement

//FUNCTION DECLARATIONS
//Movement Function Declarations
void forward(int duration);
void backward(int duration);
void traverse_left(int duration);
void traverse_left(int duration);
void adjust_right ( int duration );
void adjust_left ( int duration );
void halt ();

//Boolean function to test black strip
bool is_black_line();

//IR & Ultrasonic Test Function Declarations
void ir_and_ultrasonic_test();

//Colour Challenge Function Declarations
// bool colour_challenge();
int get_avg_reading(int times);
int determine_colour();
bool colour_challenge();
void despacito();
//Returns true if any other colour than black, otherwise false

float colour_array[] = {0, 0, 0}; // brightness readings of LDR of light from r, g, b LEDs
//float white_array[] = {850, 800, 950}; // calibrated white readings
//float black_array[] = {300, 300, 340}; // calibrated black readings
//float grey_diff[] = {0,0,0};

//Sound Challenge Function Declarations
bool sound_challenge();
int average(int arr[], int len);




//ENTIRE MAIN FUNCTION
void setup() {
  Serial.begin(9600);
  
  while (true) {
    
    forward(50);
    //IR Test and adjust accordingly (delay is 50)
    ir_and_ultrasonic_test();
    //delay(50);
    
    //Test for black strip
    if (is_black_line()) {

      //if sound is loud enough (threshold voltage to be determined)
      if (sound_challenge()) {
        //run sound challenge
        continue;
        
      } else {
        //if not loud enough
        //run colour challenge
        if (colour_challenge()) {
          //if any colour other than black
          continue;
        } else {
          //if colour is black
          break;
        }
      }
    }
  }
      
  //Play despacito
  despacito();
}


    //IR Test and adjust accordingly (delay is 50)
    //Test for black strip
    // if there is a black strip
    //    if sound is loud enough (threshold voltage to be determined)
    //      run sound challenge     
    //      CONTINUE (go back to start of the loop)
    //    else 
    //      if colour_challenge == true 
    //        CONTINUE
    //      else
    //        break
    // else 
    //   CONTINUE

void loop() {
}


//CODE ARCHIVES
//Despacito
void despacito() {
  buzzer.tone(1174, 700); // des...
  buzzer.tone(1109, 700); // pa...
  buzzer.tone(987, 400); // ci
  buzzer.tone(740, 200); // to
  delay(200);
  buzzer.tone(740, 80);
  delay(100);
  buzzer.tone(740, 80);
  delay(100);
  buzzer.tone(740, 80); 
  delay(100);
  buzzer.tone(740, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 400);
  buzzer.tone(880, 200);
  buzzer.tone(988, 400);
  buzzer.tone(784, 400);
  delay(200); // line 2
  buzzer.tone(784, 80);
  delay(100);
  buzzer.tone(784, 80);
  delay(100);
  buzzer.tone(784, 80);
  delay(100);
  buzzer.tone(784, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 400);
  buzzer.tone(1109, 200);
  buzzer.tone(1175, 400);
  buzzer.tone(880, 400);
  delay(200); // line 3
  buzzer.tone(880, 80);
  delay(100);
  buzzer.tone(880, 80);
  delay(100);
  buzzer.tone(880, 80);
  delay(100);
  buzzer.tone(880, 80);
  delay(100);
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 400);
  buzzer.tone(1300, 275);
  delay(50);
  buzzer.tone(1300, 275);
  buzzer.tone(1109, 400);
}

//Code for Colour Challenge
bool colour_challenge() {

  led.setpin(13); // setting up LED

  led.setColor(255, 0, 0);
  led.show();
  delay(RGBdelay);
  colour_array[0] = get_avg_reading(5); // reading from red LED

  led.setColor(0, 255, 0);
  led.show();
  delay(RGBdelay);
  colour_array[1] = get_avg_reading(5); // reading from green LED
  
  led.setColor(0, 0, 255);
  led.show();
  delay(RGBdelay);
  colour_array[2] = get_avg_reading(5); // reading from blue LED

  led.setColor(0, 0, 0); // turning off LEDs
  led.show();

  for (int j = 0; j <= 2; j++) {
    Serial.println(int(colour_array[j])); // print obtained RGB values
  }

  Serial.println(int(determine_colour())); // print obtained colour_code
  
  if (determine_colour() == 0) { // red action: 90 deg left
    traverse_left(450);
    return true;
  }
  else if (determine_colour() == 1) { // green action: 90 deg right
    traverse_right(450);
    return true;
  }
  else if (determine_colour() == 2) { // blue action: two grids, two rights (180 deg)
    traverse_right(450);
    forward(1600); // change forward duration
    traverse_right(450);
    return true;
  }
  else if (determine_colour() == 3) { // white action: 180 turn within same grid
    traverse_left(900);
    return true;
  }
  else if (determine_colour() == 4) { // black action: end of maze! alexa play despacito
    return false;
  }
}

int determine_colour() {
  int colour_code;
  if (colour_array[0] < 700 && colour_array[1] < 700 && colour_array[2] < 700) {
    colour_code = 4; // black
  }
  else if (colour_array[0] > 900 && colour_array[1] > 900 && colour_array[2] > 900) {
    colour_code = 3; // white
  }
  else if ((abs(colour_array[0] - colour_array[1]) < 100) && (abs(colour_array[0] - colour_array[2]) < 100) && (abs(colour_array[1] - colour_array[2]) < 100)) {
    colour_code = 1; // green
  }
  else if ((colour_array[2] > colour_array[0]) && (colour_array[2] > colour_array[1])) {
    colour_code = 2; // blue
  }
  else if ((colour_array[0] > colour_array[1]) && (colour_array[0] > colour_array[2])) {
    colour_code = 0; // red
  }
  return colour_code;
}

int get_avg_reading(int times) {
  int reading;
  int total = 0;
  for (int i = 0; i < times; i++) {
    reading = lightSensor.read(); // Brightness value from 0 - 1023. Brighter value -> board colour more similar to LED
    total += reading;
    delay(LDRdelay);
  }
  return total/times;
}
//Code for Black Line Detector
bool is_black_line() {
  int Black_line_1 = digitalRead(IR_down_1);
  int Black_line_2 = digitalRead(IR_down_2);
  float voltageDown_1 = Black_line_1 * ( 5.0 / 1023.0 );
  float voltageDown_2 = Black_line_2 * ( 5.0 / 1023.0 );

  if(voltageDown_1 > 0 && voltageDown_2 > 0){
    //forward(100);
    return false;
  }
  else if(voltageDown_1 == 0 && voltageDown_2 == 0 ){
    halt();
    return true;
  }
}

//Code for Sound Challenge
bool sound_challenge() {
  pinMode(f_A_pin, INPUT); //Reads in ADC value for 300 Hz signal
  pinMode(f_B_pin, INPUT); //Reads in ADC value for 3000 Hz signal

  //insert code here for conditional statement when encountering black strip
  //if reach black strip:
  int a[SAMPLENUM], b[SAMPLENUM];

  //Sample the signals for fA and fB
  //Ensure that the time follows Nyquist freq for the enveloped signals
  for (int i = 0; i < SAMPLENUM; i += 1) {
    a[i] = analogRead(f_A_pin);
    b[i] = analogRead(f_B_pin);
    delay(TIME);
  }

  //Measure the maximum value
  int avg_a = average(a,SAMPLENUM);
  int avg_b = average(b,SAMPLENUM);

  //If the average volume of sound detected is low, then it
  //is not sound challenge.
  int avg = (avg_a + avg_b)/2;
  if (avg < MINVOL) {
    return false;
  }
  
  //if difference of amplitude is within threshold, then turn u-turn and short circuit
  if (abs(avg_a - avg_b) < THRESHOLD) {
    //U-turn on the spot
    traverse_left(1000);
  } else if (avg_a > avg_b) {
    //left turn
    traverse_left(450);
  } else {
    //right turn
    traverse_right(450);
  }

  return true;
}

int average(int arr[], int len) {
  int sum = arr[0];
  for (int i = 1; i < len; i += 1) {
      sum += arr[i];
  }

  return sum/len;
}


//Code for IR and Ultrasonic
void ir_and_ultrasonic_test(){
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, LOW);
  pinMode(LS, OUTPUT);
  pinMode(RS, OUTPUT);
  int Black_line_1 = digitalRead(LS);
  int Black_line_2 = digitalRead(RS);
  pinMode(ULTRASONIC, INPUT);
  
  //read voltage values from IR to gauge distance
  int sensorLeft = analogRead(IRleft);
  float voltageLeft = sensorLeft * (5.0 / 1023.0);
  int sensorRight = analogRead(IRright);
  float voltageRight = sensorRight * (5.0 / 1023.0);
  //adjust to centralise mBot
  float difference = (voltageRight - voltageLeft);
  long d = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
  double distance = ((double)d * 0.034321) / 2;

  Serial.println("Left: ");
  Serial.println(voltageLeft);
  Serial.println("Right: ");
  Serial.println(voltageRight);
  Serial.println("Diff: ");
  Serial.println(difference);
  
  if ( distance > TOOCLOSEFRONT ){
        if (difference < CENTERLEFT){
            adjust_left(70);
            }
        else if (difference > CENTERRIGHT){
             adjust_right(70);
             }
        else if (difference > TOOCLOSELEFT){
             halt();
             backward(100);
             //delay(30);
             traverse_right(50);
             //delay(30);
             }
        else if (difference < TOOCLOSERIGHT){
              halt();
              backward(100);
              //delay(30);
              traverse_left(50);
              //delay(30);
             }
        else {
             forward(50);
            
             }
         }
  else if ( distance < TOOCLOSEFRONT ){
          halt();
          }
}



//Code for Movement Controls

/*
 * The parameter 'duration' determines the duration of which the motor is left on
 * A value of 1500 allows the robot to move forward about 20cm when the batteries are fully charged
 */
void forward(int duration) 
{
    left.run(-150);
    right.run(150);
    // the function left.run(n) powers the motor for n, where n is proportional to voltage across
    delay(duration);
    // this sets the duration for which the motor executes the movements
//left.stop();
    //right.stop();
    //delay(200);
    // this delay is set as a buffer so the robot does not jerk when making sudden changes in direction
    // however this value is significantly smaller for void left_adjust because the angle is small 
}

void backward( int duration ) //backward one box
{
    left.run(150);
    right.run(-150);
    delay(duration);

    //left.stop();
    //right.stop();
    //delay(200);
}

/*
 * for a 180 degree traverse, the duration is around 730 - 760 
 * for a 90 degree traverse, the duration is around 375 - 390 
 */
void traverse_left ( int duration ) 
{
     left.run(150);
     right.run(150); 
     delay(duration);

     left.stop();
     right.stop ();
     delay(200);
}

void traverse_right ( int duration ) 
{
     left.run(-150);
     right.run(-150); 
     delay(duration);

     left.stop();
     right.stop ();
     delay(200);
}
void adjust_left (int duration)  
{
     delay(50);
     left.run(150);
     right.run(150); 
     delay(duration);

     left.stop();
     right.stop ();
     delay(50);
}

void adjust_right ( int duration ) 
{
     delay(50);
     left.run(-150);
     right.run(-150); 
     delay(duration);

     left.stop();
     right.stop ();
     delay(50);
}

void halt ()
{
  left.stop();
  right.stop();
}
