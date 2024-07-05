#include <math.h> 
double   LST = 0.0; //local siderial time
double   L = 0.0;
double   HA = 0.0;
double   z = 0.0;
double   y = 0.0;
double   a = 0.0;
double   b= 0.0;

void EqToHz(double RA,double Dec, double UT, double  LAT, double  LONG, double d, double* ALT, double* AZ){
RA=RA*15;
LST=100.46 + (0.985647*d) + LONG + (15*UT);
a=LST-int(LST); // this is the fractional part of LST 
b=int(LST)%360; // this is the remainder of integral part LST, when divided by 360
L=a+b;          // this is the LST in degrees when above LST is more than 360 to bring the number in range 0 to 360 deg. .
HA = L - RA;    // hour angle 
if (HA<0){
  HA=360+HA;    // if HA is -ve then 360 is to be added
}
z=((sin(radians(Dec))*(sin(radians(LAT))))) + ((cos(radians(Dec)))*(cos(radians(LAT)))*(cos(radians(HA))));
*ALT=degrees(asin(z));
y=((sin(radians(Dec)))-((sin(radians(*ALT)))*(sin(radians(LAT)))))/((cos(radians(*ALT))*(cos(radians(LAT)))));
if(sin(radians(HA))>0){
  *AZ=360 - degrees(acos(y));
}
else{
 *AZ=degrees(acos(y));
}
}

void DJ2000(String datestr, double UT, double* d){
   double d_month1[]={0,31,59,90,120,151,181,212,243,273,304,334};
   double d_month2[]={0,31,60,91,121,152,182,213,244,274,305,335};
   double year=(datestr.substring(0,4)).toDouble();
   double month=(datestr.substring(5,7)).toDouble();
   double day=(datestr.substring(8,10)).toDouble();   
   //IstToUt(IST,&UT);  // Calculating UT in decimal hrs from IST 
  *d=364.5; //  Number of years since J2000 to begining of 2001
  for (int yr=2001;yr<year;yr++){
    if(int(yr)%4==0){
      *d=*d+366;
    }
    else{
      *d=*d+365;
    }
  }

  if(int(year)%4==0){
   *d=*d+d_month2[int(month)-1]+day+(UT/24);  
  }
  else{
   *d=*d+d_month1[int(month)-1]+day+(UT/24);
  }  
}


void IstToUt(String IST,double* UT){
  double ISTdec=(IST.substring(0,(IST.length()-3))).toFloat() + ((IST.substring((IST.length()-2))).toFloat())/60; // Converting String IST to Decimal hrs
  *UT=ISTdec-5.5; // Converting IST in hrs to UTC in hrs
}