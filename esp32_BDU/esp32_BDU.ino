#include <PS4Controller.h>
#include <ESP32Servo.h>
#define Track_right 16//1
unsigned long lastTimeStamp = 0;

Servo servo1;
Servo servo2;
//resources
//https://www.youtube.com/watch?v=_B3gWd3A_SI <- arm
//https://www.youtube.com/watch?v=I7IFsQ4tQU8&t=218s <- H-bridge
//https://www.youtube.com/watch?v=dRysvxQfVDw <- use PS4 Controller with ESP32
//
//ps4 controller mac address 30:c6:f7:04:73:5e
void notify()
{
  char messageString[200];
  sprintf(messageString, "%4d,%4d,%4d,%4d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d",// logs all controller attributes 
  PS4.LStickX(),
  PS4.LStickY(),
  PS4.RStickX(),
  PS4.RStickY(),
  PS4.Left(),
  PS4.Down(),
  PS4.Right(),
  PS4.Up(),
  PS4.Square(),
  PS4.Cross(),
  PS4.Circle(),
  PS4.Triangle(),
  PS4.L1(),
  PS4.R1(),
  PS4.L2(),
  PS4.R2(),  
  PS4.Share(),
  PS4.Options(),
  PS4.PSButton(),
  PS4.Touchpad(),
  PS4.Charging(),
  PS4.Audio(),
  PS4.Mic(),
  PS4.Battery());

  //Only needed to print the message properly on serial monitor. Else we dont need it.
  if (millis() - lastTimeStamp > 50)
  {
    Serial.println(messageString);
    lastTimeStamp = millis();
  }
}

void onConnect()
{
  Serial.println("Connected!.");
  Serial.println(servo1.read());
}

void onDisConnect()
{
  Serial.println("Disconnected!.");    
}

void setup() 
{
  Serial.begin(115200);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");
  //servo1.attach(16);
  servo2.attach(17);
  pinMode(Track_right, OUTPUT);  

}
int pos = 0;  
void loop()       
{
  bool servo1Flag = PS4.Triangle();

  
  
  /*  if(PS4.LStickY()>50 || PS4.LStickY() <-50 && !servo1Flag) {
      servo1.write(PS4.LStickY());
    } 

    if(PS4.RStickY() >50 || PS4.RStickY() < -50 && !servo1Flag){
      servo2.write(PS4.RStickY());
    }*/


  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
   //servo1.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    //servo1.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
  }
 digitalWrite(Track_right,HIGH);// tell pin 16 to move the right track

}
