#include <MeMCore.h>

MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);
MeDCMotor left(M1);
MeDCMotor right(M2);
MeBuzzer buzzer;

#define RGBdelay 200 // delay before starting measurement to allow LDR to stabilize
#define LDRdelay 50 // delay between each measurement

float colour_array[] = {0, 0, 0}; // brightness readings of LDR of light from r, g, b LEDs
float white_array[] = {850, 800, 950}; // calibrated white readings
float black_array[] = {300, 300, 340}; // calibrated black readings     
float grey_diff[] = {0,0,0};

// highest brightness reading -> colour of board most similar to that LED

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i <= 2; i++) {
    grey_diff[i] = white_array[i] - black_array[i]; // setting up grey_diff
  }
  led.setpin(13); // setting up LED
  colour_sensor(); // runs just once
}

void loop() {
  
}

void colour_sensor() {
  led.setColor(255, 0, 0);
  led.show();
  delay(RGBdelay);
  colour_array[0] = get_avg_reading(5); // reading from red LED
  colour_array[0] = (colour_array[0] - black_array[0])/(grey_diff[0])*255; // formula to obtain RGB value from brightness value

  led.setColor(0, 255, 0);
  led.show();
  delay(RGBdelay);
  colour_array[1] = get_avg_reading(5); // reading from green LED
  colour_array[1] = (colour_array[1] - black_array[1])/(grey_diff[1])*255;

  led.setColor(0, 0, 255);
  led.show();
  delay(RGBdelay);
  colour_array[2] = get_avg_reading(5); // reading from blue LED
  colour_array[2] = (colour_array[2] - black_array[2])/(grey_diff[2])*255;

  led.setColor(0, 0, 0); // turning off LEDs
  led.show();

  for (int j = 0; j <= 2; j++) {
    Serial.println(int(colour_array[j])); // print obtained RGB values
  }

  Serial.println(int(determine_colour())); // print obtained colour_code
  
  if (determine_colour() == 0) { // red action: 90 deg left
    traverse_left(400);
  }
  else if (determine_colour() == 1) { // green action: 90 deg right
    traverse_right(400);
  }
  else if (determine_colour() == 2) { // blue action: two grids, two rights (180 deg)
    traverse_right(400);
    forward(200); // change forward duration
    traverse_right(400);
  }
  else if (determine_colour() == 3) { // orange action: two grids, two lefts (180 deg)
    traverse_left(400);
    forward(200); // change forward duration
    traverse_left(400);
  }
  else if (determine_colour() == 4) { // white action: 180 turn within same grid
    traverse_left(800);
  }
  else if (determine_colour() == 5) { // black action: end of maze! alexa play despacito
    despacito();
  }
  
}

int determine_colour() {
  int colour_code;
  if (colour_array[0] < 50 && colour_array[1] < 50 && colour_array[2] < 50) {
    colour_code = 5; // black
  }
  else if (colour_array[0] > 200 && colour_array[1] > 200 && colour_array[2] > 200) {
    colour_code = 4; // white
  }
  else if ((colour_array[2] > colour_array[0]) && (colour_array[2] > colour_array[1])) {
    colour_code = 2; // blue
  }
  else if ((colour_array[1] > colour_array[0]) && (colour_array[1] > colour_array[2])) {
    colour_code = 1; // green
  }
  else if ((colour_array[0] > colour_array[1]) && (colour_array[0] > colour_array[2]) && (colour_array[0] < 212)) { // feel free to adjust threshold red value
    colour_code = 0; // red
  }
  else if ((colour_array[0] > colour_array[1]) && (colour_array[0] > colour_array[2]) && (colour_array[0] > 212)) {
    colour_code = 3; // orange
  }
  return colour_code;
  
}

int get_avg_reading(int times) { // takes 'times' number of LDR readings and returns the average of them
  int reading;
  int total = 0;
  for (int i = 0; i < times; i++) {
    reading = lightSensor.read(); // Brightness value from 0 - 1023. Brighter value -> board colour more similar to LED
    total += reading;
    delay(LDRdelay);
  }
  return total/times;
}

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

// movement code below

void forward(int duration) 
{
    left.run(-150);
    right.run(150);
    // the function left.run(n) powers the motor for n, where n is proportional to voltage across
    delay(duration);
    // this sets the duration for which the motor executes the movements

    left.stop();
    right.stop();
    delay(200);
    // this delay is set as a buffer so the robot does not jerk when making sudden changes in direction
    // however this value is significantly smaller for void left_adjust because the angle is small 
}

void backward( int duration ) //backward one box
{
    left.run(150);
    right.run(-150);
    delay(duration);

    left.stop();
    right.stop();
    delay(200);
}

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
