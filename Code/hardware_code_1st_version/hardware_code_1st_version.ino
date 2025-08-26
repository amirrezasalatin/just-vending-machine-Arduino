#include <Servo.h>
Servo my_servo;

String command = "";

void setup() {
  pinMode(6, OUTPUT); //Enable of Servo motors
  pinMode(7, OUTPUT); //Enable of water pumps

  //pin for led + servo motors//
  //select pin of demux-servo
  pinMode(3, OUTPUT); //S0
  pinMode(4, OUTPUT); //S1
  pinMode(5, OUTPUT); //S2
  //Output pin of demux-servo
  pinMode(11, OUTPUT);
  my_servo.attach(11);
  my_servo.write(0);
  //////////////////////////////

  //pin for led + water pump//
  //select pin of demux-pump
  pinMode(8, OUTPUT); //P0
  pinMode(9, OUTPUT); //P1
  pinMode(10, OUTPUT); //P2
  //Output pin of demux-pump
  pinMode(13, OUTPUT);
  //////////////////////////////

  Serial.begin(9600);
}

int number_button = 0;

void loop() {
  number_button = 0;
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processCommand(command);
      command = ""; //reset command after process finished
    } else {
      command += c;
    }
  }
  digitalWrite(6, 1);
  digitalWrite(7, 1);
}

void processCommand(String cmd) 
{
  cmd.trim();
  if(cmd[0] == 'B')
    number_button = cmd[1] - '0';
  //give number of button from UI and put in number_button//
  if (number_button >= 1 && number_button <= 5) {
    //Turn on enables
    digitalWrite(6, 0);
    digitalWrite(7, 0);
    //set select of pump on first pump//
    digitalWrite(8, bitRead(number_button - 1, 0)); //P0 = x
    digitalWrite(9, bitRead(number_button - 1, 1)); //P1 = x
    digitalWrite(10, bitRead(number_button - 1, 2)); //P2 = x
    //write output 1//
    digitalWrite(13, 0);
    delay(2700);
    digitalWrite(13, 1);
    ////////////////////////////////////
    delay(2000);
    //set select of servo on first servo//
    digitalWrite(3, bitRead(number_button - 1, 0)); //S0 = x
    digitalWrite(4, bitRead(number_button - 1, 1)); //S1 = x
    digitalWrite(5, bitRead(number_button - 1, 2)); //S2 = x
    //write output 1//
    my_servo.write(90);
    delay(2700);
    my_servo.write(0);
    //////////////////////////////////////
    delay(2000);
    Serial.println("F");
  }
  else if(number_button == 6)
  {
    digitalWrite(6, 0);
    digitalWrite(7, 0);
    //set select of pump//
    digitalWrite(8, bitRead(number_button - 1, 0)); //P0 = x
    digitalWrite(9, bitRead(number_button - 1, 1)); //P1 = x
    digitalWrite(10, bitRead(number_button - 1, 2)); //P2 = x
    //write output 1//
    digitalWrite(13, 0);
    delay(2700);
    digitalWrite(13, 1);
    ////////////////////////////////////
    for(int j = number_button;j>= 4;j--)
    {
      digitalWrite(3, bitRead(j - 1, 0)); //S0 = x
      digitalWrite(4, bitRead(j - 1, 1)); //S1 = x
      digitalWrite(5, bitRead(j - 1, 2)); //S2 = x
      //write output 1//
      my_servo.write(90);
      delay(2700);
      my_servo.write(0);
    }
    delay(2000);
    //////////////////////////////////////
    Serial.println("F");
  }else {
    Serial.println("Invalid number_button. Please enter 1 to 6.");
  }
  //Turn off enables
  digitalWrite(6, 1);
  digitalWrite(7, 1);
}