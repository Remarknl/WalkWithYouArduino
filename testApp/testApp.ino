// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo
Servo myservo2;
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
byte val2;
int val3;
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
  myservo2.attach(9);
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  //Serial.write(val);
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 
  
  if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):
    val2 = Serial.read();
    Serial.write(val2);
    val3 = (int) val2;
    myservo2.write(val3);
  }
  delay(10);                           // waits for the servo to get there 
} 
