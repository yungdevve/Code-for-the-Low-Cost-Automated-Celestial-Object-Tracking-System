

// Include the Arduino Math.h library:
#include <math.h>
#include <Stepper.h>
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
#include "AltAz.h"
#include "Tracker.h"
#include "MotorSetting.h"
double   RA = 23.60055; // RA in decimal hours
double   Dec = 0.17275; // dec in decimal hours
String   IST = "13:40";  //Indian Standard Time in "HH:MM" format
String   Date="2023/03/14"; //Date in "YYYY/MM/DD" format
double   LAT = 24.8333; // latitude of the location 
double   LONG = 92.7789; // longitude of the location 
double   ALT = 0.0; // Altitude (To be calculated)
double   AZ = 0.0; // Azimuth  (To be calculated)
double   d=0; // Number of days from J2000 (To be calculated)
double   UT=0; //Universal Time (To be calculated)
double   i=0; //Index to detect first run
double   delaytime=60000; //Delay time in milliseconds
int      StartTracking=0; //A flag to start tracking
String   btCommand=""; //Command 
String   btCommand2="";
// Include the Arduino Stepper.h library:
//define the no. of steps per revolution:

void setup() {
   //begin the serial communication at a baud rate of 9600:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void incData(){
if(btCommand2.substring(0,3)=="MC:"){
 //Serial.println (btCommand.substring(3,btCommand.length())); 
  //setMotor(btCommand.substring(3,btCommand.length())); //Check this carefully 
 
  setMotor(btCommand2);
//  btCommand2="";
}
if(btCommand2.substring(0,3)=="RA:"){
  RA=btCommand2.substring(3,btCommand2.length()).toDouble(); //Check this carefully 
  //Serial.println(RA);
 // btCommand="";
}
if(btCommand2.substring(0,3)=="DC:"){
  Dec=btCommand2.substring(3,btCommand2.length()).toDouble(); //Check this carefully 
  //Serial.println(Dec);
 // btCommand="";
}
if(btCommand2.substring(0,3)=="TM:"){
  IST=btCommand2.substring(3,btCommand2.length()); //Check this carefully 
 // btCommand="";
}
if(btCommand2.substring(0,3)=="DT:"){
  Date=btCommand2.substring(3,btCommand2.length()); //Check this carefully 
 // btCommand="";
}
if(btCommand2.substring(0,3)=="LA:"){
  LAT=btCommand2.substring(3,btCommand2.length()).toDouble(); //Check this carefully 
//  btCommand="";
}
if(btCommand2.substring(0,3)=="LO:"){
  LONG=btCommand2.substring(3,btCommand2.length()).toDouble(); //Check this carefully 
//  btCommand="";
}
if(btCommand2.substring(0,3)=="TR:"){
  StartTracking=btCommand2.substring(3,btCommand2.length()).toInt(); //Check this carefully 
//  btCommand="";
}

}

void loop() {
  if(mySerial.available()){ 
    btCommand += char(mySerial.read());
     if(btCommand.substring(btCommand.length()-1,btCommand.length())=="/"){
        btCommand2=btCommand.substring(0,btCommand.length()-1);
        btCommand ="";
        }
}
//Serial.println(btCommand2);
//setMotor(btCommand2);
//Serial.println("Ok");
//delay(500);
//btCommand2="";
 incData();
/*
if(btCommand2.substring(0,3)=="MC:"){
  setMotor(btCommand2);
  btCommand2="";
}*/

if (StartTracking==1){
    if (i==0){
    IstToUt(IST,&UT); // Caclulating UT in decimal hrs for the starting time
    }
    else{
      UT=UT+((delaytime/1000)/3600); // Updating UT during runtime
    }
    DJ2000(Date,UT,&d); // Calculating d 
    EqToHz(RA,Dec,UT,LAT,LONG,d,&ALT,&AZ); // Calculating ALT and AZ
    Serial.print("UTC=");
    Serial.println(UT);
    tracking(i,ALT,AZ);
    i=i+1;    
    delay(delaytime);
}

 
}
