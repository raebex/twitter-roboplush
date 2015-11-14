#include <Servo.h>

//servos
Servo myservo;
Servo myservoTwo;
int pos1 = 0;
int pos2 = 30;
long interval = 15;
int t = 0; //iterator for servo delay
int motorSteps = 0;

//capture incoming serial data from node server
char incomingByte = 0;

//matrix
int outTop = 13;
int outBottom = 12;
int in1 = 11;
int in2 = 10;
int in3 = 9;
int in4 = 8;
int in5 = 7;

//eyes
const int eyes = 6;

void setup() {
  //eyes
   pinMode(eyes, OUTPUT);
  
   //matrix
   pinMode(outTop, OUTPUT);
   pinMode(outBottom, OUTPUT);
   pinMode(in1, OUTPUT);
   pinMode(in2, OUTPUT);
   pinMode(in3, OUTPUT);
   pinMode(in4, OUTPUT);
   pinMode(in5, OUTPUT);
   
   //servos
   myservo.attach(3); 
   myservo.write(30);   
   myservoTwo.attach(5);
   myservoTwo.write(0);
   
   //plushie starts off with neutral expression
   //and eyes on
   neutral();
   digitalWrite(eyes, HIGH);
   
   //start serial
   Serial.begin(9600);   
    
}

void loop() {
  //check if serial is available
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == 49) { 
      //if tag is '1'
      happy();
    }else if(incomingByte == 50) {
      //if tag is '2'
      sad();
    }else if(incomingByte == 51) {
      //if tag is '3' or something else
      for(int i = 0; i<3; i++) {
         meh();
      }
    }
  } else {
    //otherwise, neutral
    neutral();
  }
}

void neutral(){   
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(outTop, LOW);
  digitalWrite(outBottom, HIGH);
}

void happy(){
  for (int i = 0; i < 3000; i++) {  
    digitalWrite(in1, HIGH);  
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, HIGH);
    digitalWrite(outTop, LOW);
    digitalWrite(outBottom, HIGH);
    delay(1); 
    
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, LOW);
    digitalWrite(outTop, HIGH);
    digitalWrite(outBottom, LOW);
    delay(1);
  }
}

void sad(){
  for (int i = 0; i < 2000; i++) {  
    digitalWrite(in1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, HIGH);
    digitalWrite(outTop, HIGH);
    digitalWrite(outBottom, LOW);
    delay(1);
   
    digitalWrite(in1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, LOW);
    digitalWrite(outTop, LOW);
    digitalWrite(outBottom, HIGH);
    delay(1); 
  }
}

void meh(){
   digitalWrite(in1, HIGH);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(in2, HIGH);
   digitalWrite(in3, HIGH);
   digitalWrite(in4, HIGH);
   digitalWrite(in5, HIGH);
   digitalWrite(outTop, LOW);
   digitalWrite(outBottom, HIGH);
      
   t = 0;
   motorSteps = 0;
   for (int i = 0; i < 30; i++) {
      while(motorSteps < 30) {       
        pos1 = 0 + motorSteps; // servo1 from 30 to 0 degrees
        pos2 = 30 - motorSteps; // servo2 from 0 to 30 degrees
        
        if(t == 0){
          myservo.write(pos1);
          myservoTwo.write(pos2);
          motorSteps = motorSteps +1; 
        }
        
        t = (t+1) % 10;
       delay(2);
      }  
   }
}
