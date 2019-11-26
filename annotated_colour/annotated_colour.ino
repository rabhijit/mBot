#include "stdbool.h"
#include <MeMCore.h>

MeDCMotor left(M1);
MeDCMotor right(M2);
MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);
MeBuzzer buzzer;

#define RGBdelay 200 // delay before starting measurement to allow LDR to stabilize
#define LDRdelay 50 // delay between each measurement

/* array of brightness values detected by LDR when r, g, b LEDs are flashed respectively. 
 * Brightness values range from 0-1023
 */
float colour_array[] = {0, 0, 0}; 

void setup() {
  colour_challenge();
}

/**
 * Sets the two LEDs of the mBot to red, green and blue and sets brightness readings of LDR from each
 * LED to the array colour_array. Calls determine_colour function to determine colour of board and 
 * based on returned value from determine_colour, does appropriate movement and returns true or false
 * to keep the main function looping or break the loop if black is detected (the finish line)
 * 
 * @return true if black is not detected, false if black is detected
 */

bool colour_challenge() {

  led.setpin(13); // setting up LED

  led.setColor(255, 0, 0); // setting LEDs to Red
  led.show(); // needs to run for LEDs to light
  delay(RGBdelay); // delay before starting measurement to allow LDR to stabilize
  colour_array[0] = get_avg_reading(5); // brightness reading from red LED

  led.setColor(0, 255, 0); // setting LEDs to Green
  led.show();
  delay(RGBdelay);
  colour_array[1] = get_avg_reading(5); // brightness reading from green LED
  
  led.setColor(0, 0, 255); // setting LEDs to Blue
  led.show();
  delay(RGBdelay);
  colour_array[2] = get_avg_reading(5); // brightness reading from blue LED

  led.setColor(0, 0, 0); // turning off LEDs
  led.show();

  /* the following if-else statements run the necessary actions based on the value returned from the
   *  determine_colour function, which returns a value based on brightness readings just obtained 
   */
  
  if (determine_colour() == 0) { // 0 for red. Action: 90 deg left
    traverse_left(450);
    return true; // return true to continue the main function
  }
  else if (determine_colour() == 1) { // 1 for green. Action: 90 deg right
    traverse_right(450);
    return true;
  }
  else if (determine_colour() == 2) { // 2 for blue. Action: two grids, two rights (180 deg)
    traverse_right(450);
    forward(1600); // change forward duration
    traverse_right(450);
    return true;
  }
  else if (determine_colour() == 3) { // 3 for white. Action: 180 turn within same grid
    traverse_left(900);
    return true;
  }
  else if (determine_colour() == 4) { // 4 for black. Action: end of maze! play despacito
    return false; // returns false to break the main function from looping
  }
}

/**
 * Based on brightness values in integer array colour_array (as set by function colour_challenge), decides
 * colour of the board and returns an integer from 0-4 to represent each possible colour (0-4 for red, green, blue,
 * blue, white and black respectively). Brightness tests are decided based on brightness values observed 
 * for each colour in lab
 * 
 * @return The colour code representing the chosen colour.
 */

int determine_colour() {
  int colour_code;
  if (colour_array[0] < 700 && colour_array[1] < 700 && colour_array[2] < 700) { 
    // red, green, blue < 700: black
    colour_code = 4; // black
  }
  else if (colour_array[0] > 900 && colour_array[1] > 900 && colour_array[2] > 900) {
    // red, green, blue > 900: white
    colour_code = 3; // white
  }
  else if ((abs(colour_array[0] - colour_array[1]) < 100) && (abs(colour_array[0] - colour_array[2]) < 100) && (abs(colour_array[1] - colour_array[2]) < 100)) {
    // modulus(red - green) < 100 and modulus(red - blue) < 100 and modulus(green - blue) < 100
    colour_code = 1; // green
  }
  else if ((colour_array[2] > colour_array[0]) && (colour_array[2] > colour_array[1])) {
    // blue value > red value and blue value > green value
    colour_code = 2; // blue
  }
  else if ((colour_array[0] > colour_array[1]) && (colour_array[0] > colour_array[2])) {
    // red value > green value and red value > blue value
    colour_code = 0; // red
  }
  return colour_code;
}

/**
 * Reads in the number of times to take a brightness reading, takes a brightness reading from the LDR
 * that number of times, and returns the average of those brightness readings.
 * 
 * @param[in] times The number of times to take a brightness reading.
 * @return The average of the obtained brightness readings.
 */

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

/**
 * Plays the chorus of song Despacito using the MeBuzzer library. Tones are played based on the frequencies 
 * and durations of each note in the actual song.
 */

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
  delay(200); // 2nd line
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
  delay(200); // 3rd line
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
