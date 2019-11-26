#include <MeMCore.h>
MeDCMotor left(M1);
MeDCMotor right(M2);
void forward(int duration);
void backward(int duration);
void traverse_left(int duration);
void traverse_left(int duration);
void adjust_right ( int duration );
void adjust_left ( int duration );
void halt ();
void setup() 
{
  /*
   * Combining the basic movements to make complex movements 
   * Right turn:
   * traverse_right (390); forward ( 1400 ); traverse_right(390);
   * These values passed to the functions have to fine tuned according to the surface and distance of the maze
   */
  traverse_right ( 390 );
  forward ( 1200 );
  traverse_right ( 390 );

  halt();

  traverse_left ( 400 );
  backward ( 1000 );

  for ( int i = 0; i < 10; i += 1 )
  {
  adjust_right(100);
  forward(100);
  }
}

void loop ()
{ 
  
}

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
