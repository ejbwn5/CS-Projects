#include <Servo.h>

Servo servo1;                 //right hand side
Servo servo2;                 //left hand side

const int buttonPin = 16;     //pin for the button input (active low)

const int servoPin = 11;      //pin for servo1
const int servoPin2 = 12;     //pin for servo2

const int angle1 = 86;       //servo angle for DRS activated
const int angle2 = 0;       //servo angle for DRS deactivated

int DRSactivate = 0;        //keeps track of DRS state
int debounceCount=0;        //debouncing counter

void servoWrite()
{
  if (DRSactivate == LOW) //DRS off
  {
    servo1.write(angle2);    
    servo2.write(angle1);   
  }
  else                    //DRS on
  {
    servo1.write(angle1);    
    servo2.write(angle2);   
  }
}

void setup() {    
  pinMode(buttonPin, INPUT_PULLUP);  //pull pin high by default
  servo1.attach(servoPin);           //attach servos
  servo2.attach(servoPin2);
  DRSactivate = digitalRead(buttonPin); //get initial DRS state
  servoWrite();                         //set servos
}

void loop() {

  //if button state is opposite of current state, add to debouncing counter
  if (digitalRead(buttonPin) == !DRSactivate)
  {
    debounceCount++;
  }
  else //if button state is the same as current state reset counter
  {
    debounceCount=0;
  }

  //if there have been 3 consecutive opposite reads, switch servo state
  if (debounceCount > 2)
  {
    DRSactivate = !DRSactivate; //invert state
    servoWrite();               //write to servos
    debounceCount=0;            //reset counter
  }
  delay(10);              //wait a brief moment before running again
}
