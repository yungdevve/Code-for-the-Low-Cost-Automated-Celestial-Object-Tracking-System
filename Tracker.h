#include <Stepper.h>
double   ALT1 = 0.0;
double   AZ1 = 0.0;
double   delALT = 0.0;
double   delAZ = 0.0;
double   errorALT = 0.0;
double   errorAZ = 0.0;
double   errorALT1 = 0.0;
double   errorAZ1 = 0.0;
double   stepsALT = 0.0;
double   stepsAZ = 0.0;
const int StepsPerRevolution = 2048;

// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver
// Pin 4 to IN4 on tne ULN2003 driver
// Pin 5 to IN3 on tne UNL2003 driver
// Pin 6 to IN2 on the UNL2003 driver
// pin 7 to IN1 on the UNL2003 driver
// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper1 = Stepper(StepsPerRevolution,8,10,9,11); //Azimuth motor
Stepper myStepper2 = Stepper(StepsPerRevolution,4,6,5,7); //Altitude motor

void tracking(int i, double ALT, double AZ){
myStepper1.setSpeed(10);
myStepper2.setSpeed(10);
    if (i==0){
  delALT=((90-ALT)*2048)/360;
  delAZ=(AZ*2048)/360;
  ALT1=ALT;
  AZ1=AZ;
}
else{
  delALT=((ALT1-ALT)*2048)/360;
  delAZ=((AZ-AZ1)*2048)/360;
  ALT1=ALT;
  AZ1=AZ;
}

stepsALT=floor(delALT);
stepsAZ=floor(delAZ);
errorALT=delALT-floor(delALT);
errorAZ=delAZ-floor(delAZ);

if (i==0){
  errorALT=0;
  errorAZ=0;
  errorALT1=errorALT;
  errorAZ1=errorAZ;
}
else {
  errorALT=errorALT+errorALT1;
  errorAZ=errorAZ+errorAZ1;
  if(errorALT>=1){
    stepsALT=stepsALT + 1;
    errorALT=errorALT - 1;
  }
  if(errorAZ>=1){
    stepsAZ=stepsAZ + 1;
    errorAZ=errorAZ - 1;
  }
  errorALT1=errorALT;
  errorAZ1=errorAZ;  
}

Serial.print("Altitude=");
Serial.println(ALT,4);
Serial.print("Azimuth=");
Serial.println(AZ,4);
Serial.print("Difference of Altitude=");
Serial.println(delALT);
Serial.print("Difference of Azimuth=");
Serial.println(delAZ);
Serial.print("Error in Altitude=");
Serial.println(errorALT);
Serial.print("Error in Azimuth=");
Serial.println(errorAZ);
Serial.print("Steps taken by the Altitude motor=");
Serial.println(stepsALT); 
Serial.print("Steps taken by the Azimuth motor=");
Serial.println(stepsAZ);

Serial.println("clockwise");
myStepper2.step(stepsAZ);
//delay(500);
Serial.println("counterclockwise");
myStepper1.step(-stepsALT);
//delay(500);
}