#include <Servo.h> //используем библиотеку для работы с сервоприводом

Servo servoHorizontal;
Servo servoVertical;
int servoHorizontal_pos;
int servoVertical_pos;
int pin;
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
 *
 * i - light green
 * o - light red
 * p - shut down
 */

void setup() //процедура setup
{

  servoHorizontal.attach(10);
  servoVertical.attach(11);
  Serial.begin(9600);
  servoHorizontal_pos = 90;
  servoVertical_pos = 90;
  command = '0';
  pinMode(13, OUTPUT);
  delay(100);
  pinMode(12, OUTPUT);
  delay(100);
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
  if (Serial.available()>0)
  {
      command = Serial.read();
  }
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
  else if(command == 'i')
  {
    if(pin != 13)
    {
      digitalWrite(pin, LOW);
      delay(1000);
      pin = 13;
      digitalWrite(pin, HIGH);
      delay(1000);
    }
  }
  else if(command == 'o')
  {
    if(pin != 12)
    {
      digitalWrite(pin, LOW);
      delay(1000);
      pin = 12;
      digitalWrite(pin, HIGH);
      delay(1000);
    }
  }
  else if(command == 'p')
  {
    digitalWrite(pin, LOW);
    delay(1000);
  }
}
