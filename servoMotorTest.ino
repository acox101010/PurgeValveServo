//THIS SCRIPT ACTUATES A 4.8V SERVO FOR CONTROLING A REGULATOR PURGE VALVE 
//THIS WAS DEVELOPED TO AUTOMATE THE PURGE CONTROL FOR THE HUD LED TEST

#include <Servo.h> //library for interfacing with servo motor
#define delayTime 30 //delay time set at 30 milliseconds

int p1Button = 7; //Push button 1 (purge) input set to digital pin 7
int p2Button = 8; //Push button 2 (close) input set to digital pin 8
int pb1Val = 0; //creates variable for pushbutton 1
int pb2Val = 0; //creates variable for pushbutton 2

Servo myservo; // create servo object to control a servo

int pos = 0; //Variable storing servo position

void setup() {
  pinMode(p1Button, INPUT); //Sets push button 1 as an input
  pinMode(p2Button, INPUT); //Sets push button 2 as an input
  myservo.attach(9);  // attaches the servo signal to pin 9 
  Serial.begin(9600); //Open comms to the serial monitor
}

//Create function for rotating servo +90deg from 0
void Open_V() {
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(delayTime);
    pb1Val = 0;
    pos = 90;
    }
}

//Create function for rotating servo -90deg to 0
void Close_V() {
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(delayTime);
    pb2Val = 0;
    pos = 0;
    }
}

//Creates function for increasing pushbutton 1 variable
void pb1_count() {
  pb1Val = pb1Val+1; 
}
//Creates function for increasing pushbutton 2 variable
void pb2_count() {
  pb2Val = pb2Val+1; 
}

//////////////////////////////////////LOOP SECTION/////////////////////////////////////////////////
void loop() {
//Checks if pushbutton 1 is pulled low. If so, it increments +1.
  if (digitalRead(p1Button) == LOW){
    delay(100);
    pb1_count();
    Serial.print("Pin1 Value");
    Serial.println(pb1Val);
  } 
  if (pb1Val >= 2){
    Open_V();
    //delay(delayTime);
  }
}
