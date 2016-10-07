/*
  Блымаем светодиодиком, можно потом юзать для включения/выключения красной/зеленой лампочек
  Светодиод подключать к 13 пину через резистор(крч у светодиода 2 лапки! самую длинную подключаем к
    резистору, а резистор к 13 пину. Вторую ножку светодиода вставляем в граунд (GND)  
*/

/*
    13pin - green;
    12pin - red;
    u - none
    i - light green
    o - light red
    p - shut down
*/
int pin;
char command;

void setup() {
    
  pinMode(13, OUTPUT); //светодиодик в 13 пине (:_:)
  pinMode(12, OUTPUT);
  command = 'u';
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0)
  {
      command = Serial.read();
  }
  if(command == 'u')
  {
    //none
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
