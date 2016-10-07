#include <Servo.h> //используем библиотеку для работы с сервоприводом

Servo servoHorizontal;
Servo servoVertical;
int servoHorizontal_pos;
int servoVertical_pos;
char command;
/*
 * COMMANDS: (H / V)
 * 
 * 0 - NONE, NONE
 * 1 - NONE, UP
 * 2 - NONE, DOWN
 * 3 - RIGHT, NONE
 * 4 - LEFT, NONE
 * 5 - RIGHT, UP
 * 6 - RIGHT, DOWN
 * 7 - LEFT, UP
 * 8 - LEFT, DOWN
 */

void setup() //процедура setup
{

  servoHorizontal.attach(10);
  servoVertical.attach(11);
  Serial.begin(9600);
  servoHorizontal_pos = 90;
  servoVertical_pos = 90;
  command = '0';
  servoVertical.write(servoVertical_pos);
  delay(100);
  servoHorizontal.write(servoHorizontal_pos);
  delay(100);

}

void turnUp()
{
  if (servoVertical_pos > 0)
  {
    servoVertical.write(servoVertical_pos++);
    delay(150);
  }
}

void turnDown()
{
  if (servoVertical_pos < 180)
  {
    servoVertical.write(servoVertical_pos--);
    delay(150);
  }
}

void turnLeft()
{
  if (servoHorizontal_pos > 0)
  {
    servoHorizontal.write(servoHorizontal_pos--);
    delay(100);
  }
}

void turnRight()
{
  if (servoHorizontal_pos < 180)
  {
    servoHorizontal.write(servoHorizontal_pos++);
    delay(100);
  }
}
void loop()
{ 
  if (command == '0')
  {
    // NONE
  }
  else if (command == '1')
  {
    turnUp();
  }
  else if (command == '2')
  {
    turnDown();
  }
  else if (command == '3')
  {
    turnRight();
  }
  else if (command == '4')
  {
    turnLeft();
  }
  else if (command == '5')
  {
    turnRight();
    turnUp();
  }
  else if (command == '6')
  {
    turnRight();
    turnDown();
  }
  else if (command == '7')
  {
    turnLeft();
    turnUp();
  }
  else if (command == '8')
  {
    turnLeft();
    turnDown();
  }
  if (Serial.available()>0)
  {
      command = Serial.read();
  }
}
