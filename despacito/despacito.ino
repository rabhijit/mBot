#include <MeMCore.h>

MeBuzzer buzzer;
MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);
MeDCMotor left(M1);
MeDCMotor right(M2);

void setup() {
  // put your setup code here, to run once:
  led.setpin(13);
}

void loop() {
  // put your main code here, to run repeatedly:
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(1174, 700); // des...
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(1109, 700); // pa...
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(987, 400); // ci
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(740, 200); // to
  delay(200);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(740, 80);
  delay(100);
  buzzer.tone(740, 80);
  delay(100);
  buzzer.tone(740, 80); 
  delay(100);
  buzzer.tone(740, 80);
  delay(100);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(988, 400);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(880, 200);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(988, 400);
  led.setColor(random(255), random(255), random(255));
  led.show();
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
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 80);
  delay(100);
  buzzer.tone(988, 400);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(1109, 200);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(1175, 400);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(880, 400);
  delay(200); // line 3
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(880, 80);
  delay(100);
  buzzer.tone(880, 80);
  delay(100);
  buzzer.tone(880, 80);
  delay(100);
  buzzer.tone(880, 80);
  delay(100);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 80);
  delay(100);
  buzzer.tone(1175, 400);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(1300, 275);
  delay(50);
  buzzer.tone(1300, 275);
  led.setColor(random(255), random(255), random(255));
  led.show();
  buzzer.tone(1109, 400);
}

// movement code

void _left (int duration)  
{
     delay(50);
     left.run(150);
     right.run(150); 
     delay(duration);

     left.stop();
     right.stop ();
     delay(50);
}

void _right ( int duration ) 
{
     delay(50);
     left.run(-150);
     right.run(-150); 
     delay(duration);

     left.stop();
     right.stop ();
     delay(50);
}
