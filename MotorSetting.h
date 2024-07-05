#include <Stepper.h>
unsigned long motorDelay1 = 0;
unsigned long motorDelay2 = 0;
int           motorDelayLength1 = 2;
int           motorDelayLength2 = 2;
int           motor1 = 0; // off=0, forward=1, reverse=2
int           motor2 = 0; // off=0, forward=1, reverse=2
Stepper myStepper4 = Stepper(StepsPerRevolution,8,10,9,11); //Azimuth motor
Stepper myStepper3 = Stepper(StepsPerRevolution,4,6,5,7); //Altitude motor
void spd(){
  if(millis()> motorDelay1 + motorDelayLength1){
    if(motorDelay1 > (4294967295-motorDelayLength1)){
      motorDelay1 = (4294967295-motorDelay1) + (motorDelayLength1-(4294967295-motorDelay1));
    }else{
      motorDelay1+=motorDelayLength1;
    }
    if(motor1>0){   //For Azimuth
      if(motor1 == 1){
        myStepper3.step(1);
      }else{
        myStepper3.step(-1);
      }
      }
    }
  if(millis()> motorDelay2 + motorDelayLength2){
    if(motorDelay2 > (4294967295-motorDelayLength2)){
      motorDelay2 = (4294967295-motorDelay2) + (motorDelayLength2-(4294967295-motorDelay2));
    }else{
      motorDelay2+=motorDelayLength2;
    }
  if(motor2>0){  //For Altitude
      if(motor2 == 1){
        myStepper4.step(1);
      }else{
        myStepper4.step(-1);
      }
      }
  }

}

//myStepper3.setSpeed(10);
//myStepper4.setSpeed(10);


void setMotor(String dfd) {

  Serial.println(dfd);
  spd();
  if(dfd=="MC:MA1ON"){
    motor1=1;
    dfd="";
  }
  if(dfd=="MC:MA1OF"){
    motor1=0;
    dfd="";
  }
  if(dfd=="MC:MA2ON"){
    motor1=2;
    dfd="";
  }
  if(dfd=="MC:MA2OF"){
    motor1=0;
    dfd="";
  }
  if(dfd=="MC:MB1ON"){
    motor2=1;
    dfd="";
  }
  if(dfd=="MC:MB1OF"){
    motor2=0;
    dfd="";
  }
  if(dfd=="MC:MB2ON"){
    motor2=2;
    dfd="";
  }
  if(dfd=="MC:MB2OF"){
    motor2=0;
    dfd="";
  }
  if(dfd.length()>7){
    motorDelayLength2=dfd.substring(6,7).toInt();
    dfd="";
    //Serial.println(String(motorDelayLength));
  }
  if(dfd.length()>7){
    motorDelayLength2=dfd.substring(6,7).toInt();
    dfd="";
    //Serial.println(String(motorDelayLength1));
  }
  

  

}



