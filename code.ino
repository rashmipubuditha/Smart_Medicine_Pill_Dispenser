//#if defined(ESP32)
//#include <WiFi.h>
//#define(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <Wire.h>
#include <RtcDS3231.h>  //RTC library
#include <EEPROM.h>
#include "Arduino.h"
#include <Stepper.h>

// #define WIFI_SSID "wifi_ID"
#define WIFI_PASSWORD "73cbqdmcijverevfd"
#define API_KEY "vG19mV1o2ZJqtuQsebcE4vr5mEJrSdZjzjmRlaWghg"
#define DATABASE_URL "database_URL/"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

#define buzz D0

RtcDS3231<TwoWire> rtcObject(Wire);

Stepper myStepper1(2048,D3,D4,D5,D6);
Stepper myStepper2(2048,D7,D8,3,1);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int AV1, AV2, AV3, pDay;
int AVR1, AVR2, AVR3;
int Years, Months, Days, Hours, Min, Sec,timeStamp, date;
String k, m1, m2, m3, iv;
int MS1[] = {1,3,0};
int MS2[] = {1,2,0};
int MS3[] = {1,3,4};
int M1, M2, M3;
int ind1, ind2, ind3;
int AH1, AM1, AH2, AM2, AH3, AM3, W;
int AHR1, AMR1, AHR2, AMR2, AHR3, AMR3;
int onv=1, ofv=0;
int motorSpeed = 10;
int rt=1;
unsigned long lm, HT = 5000;

void setup() {
 rtcObject.Begin();
 EEPROM.begin(4096);
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
 delay(10000); 
// pDay = currentTime.day(), DEC;
 myStepper1.setSpeed(motorSpeed);
 myStepper2.setSpeed(motorSpeed);
 
}

void loop() 
{
 RtcDateTime currentTime = rtcObject.GetDateTime(); 
 Years= currentTime.Year(); Months= currentTime.Month(); Days= currentTime.Day();
 Hours= currentTime.Hour(); Min= currentTime.Minute(); Sec= currentTime.Second();
 pDay = currentTime.Day(), DEC;
if (WiFi.status() == WL_CONNECTED)
 { 
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);
  delay(2000);

if (Firebase.ready()) 
  { 
//_________________For Medicine set 1_____________________
    Firebase.getString(fbdo, "MS/MS1");
    k = fbdo.to<String>();
    ind1 = k.indexOf(',');           m1 = k.substring(1, ind1);      M1 = m1.toInt(); MS1[0]=M1; EEPROM.write(40,MS1[0]);
    ind2 = k.indexOf(',', ind1+1 );  m2 = k.substring(ind1+1, ind2); M2 = m2.toInt(); MS1[1]=M2; EEPROM.write(41,MS1[1]);
    ind3 = k.indexOf(']', ind2+1 );  m3 = k.substring(ind2+1, ind3); M3 = m3.toInt(); MS1[2]=M3; EEPROM.write(42,MS1[2]);
     
//_________________For Medicine set 2_____________________
   Firebase.getString(fbdo, "MS/MS2");
    k = fbdo.to<String>();
    ind1 = k.indexOf(',');           m1 = k.substring(1, ind1);      M1 = m1.toInt(); MS2[0]=M1; EEPROM.write(20,MS2[0]);
    ind2 = k.indexOf(',', ind1+1 );  m2 = k.substring(ind1+1, ind2); M2 = m2.toInt(); MS2[1]=M2; EEPROM.write(21,MS2[1]);
    ind3 = k.indexOf(']', ind2+1 );  m3 = k.substring(ind2+1, ind3); M3 = m3.toInt(); MS2[2]=M3; EEPROM.write(22,MS2[2]);     

//_________________For Medicine set 3_____________________
   Firebase.getString(fbdo, "MS/MS3");
    k = fbdo.to<String>();
    ind1 = k.indexOf(',');           m1 = k.substring(1, ind1);      M1 = m1.toInt(); MS3[0]=M1; EEPROM.write(30,MS3[0]);
    ind2 = k.indexOf(',', ind1+1 );  m2 = k.substring(ind1+1, ind2); M2 = m2.toInt(); MS3[1]=M2; EEPROM.write(31,MS3[1]);
    ind3 = k.indexOf(']', ind2+1 );  m3 = k.substring(ind2+1, ind3); M3 = m3.toInt(); MS3[2]=M3; EEPROM.write(32,MS3[2]);
     
//_________________For Alarm 1____________________
    Firebase.getString(fbdo, "T/AH1"); iv = fbdo.to<String>();
    AH1 = iv.toInt(); EEPROM.write(10,AH1);
    Firebase.getString(fbdo, "T/AM1"); iv = fbdo.to<String>();
    AM1 = iv.toInt(); EEPROM.write(11,AM1);
    if((AM1+rt) == 60) { AHR1=AH1+1; AMR1=0; }
    else               { AHR1=AH1; AMR1=AM1+rt; }
    
//_________________For Alarm 2____________________
    Firebase.getString(fbdo, "T/AH2"); iv = fbdo.to<String>();
    AH2 = iv.toInt(); EEPROM.write(12,AH2);
    Firebase.getString(fbdo, "T/AM2"); iv = fbdo.to<String>();
    AM2 = iv.toInt(); EEPROM.write(13,AM2);
    if((AM2+rt) == 60) { AHR2=AH2+1; AMR2=0; }
    else               { AHR2=AH2; AMR2=AM2+rt; }

//_________________For Alarm 3____________________
    Firebase.getString(fbdo, "T/AH3"); iv = fbdo.to<String>();
    AH3 = iv.toInt(); EEPROM.write(14,AH3);
    Firebase.getString(fbdo, "T/AM3"); iv = fbdo.to<String>();
    AM3 = iv.toInt(); EEPROM.write(15,AM3);
    if((AM3+rt) == 60) { AHR3=AH3+1; AMR3=0; }
    else               { AHR3=AH3; AMR3=AM3+rt; }
    
  }//fb ready
  }// have network
  
//_______________________________________no network_________________________________________
else{
    
  if(EEPROM.read(10) == 77 && EEPROM.read(11) == 77)   
   {
  //A1  
    AH1=00; AM1=00;  // sokal 8 ta
    if((AM1+rt) == 60) { AHR1=AH1+1; AMR1=0; }
    else               { AHR1=AH1; AMR1=AM1+rt; }
   }
   else 
   { 
    AH1 = EEPROM.read(10); AM1 = EEPROM.read(11); 
    if((AM1+rt) == 60) { AHR1=AH1+1; AMR1=0; }
    else               { AHR1=AH1; AMR1=AM1+rt; }
   }
   
  //A2
   if(EEPROM.read(12) == 77 && EEPROM.read(13) == 77)   
   {
    AH2=00; AM2=05; // dupur 1 ta
    if((AM2+rt) == 60) { AHR2=AH2+1; AMR2=0; }
    else               { AHR2=AH2; AMR2=AM2+rt; }
   }
   else 
   { 
    AH2 = EEPROM.read(12); AM2 = EEPROM.read(13); 
    if((AM2+rt) == 60) { AHR2=AH2+1; AMR2=0; }
    else               { AHR2=AH2; AMR2=AM2+rt; }
   }
  
  //A3
   if(EEPROM.read(14) == 77 && EEPROM.read(15) == 77)   
   { 
    AH3=00; AM3=10; // rat 9 ta
    if((AM3+rt) == 60) { AHR3=AH3+1; AMR3=0; }
    else               { AHR3=AH3; AMR3=AM3+rt; }
   }
   else 
   { 
    AH3 = EEPROM.read(14); AM3 = EEPROM.read(15); 
    if((AM3+rt) == 60) { AHR3=AH3+1; AMR3=0; }
    else               { AHR3=AH3; AMR3=AM3+rt; }
   }
//________________________________Medicine set______________________________________ 

   //MS1
   if(EEPROM.read(40) == 77 && EEPROM.read(41) == 77 && EEPROM.read(42) == 77)  {}
   else { 
    MS1[0]= EEPROM.read(40); MS1[1]= EEPROM.read(41); MS1[2]= EEPROM.read(42); }
  //MS2
   if(EEPROM.read(20) == 77 && EEPROM.read(21) == 77 && EEPROM.read(22) == 77)  {}
   else { 
    MS2[0]= EEPROM.read(20); MS2[1]= EEPROM.read(21); MS2[2]= EEPROM.read(22); } 
  //MS3
   if(EEPROM.read(30) == 77 && EEPROM.read(31) == 77 && EEPROM.read(32) == 77)  {}
   else { 
    MS3[0]= EEPROM.read(30); MS3[1]= EEPROM.read(31); MS3[2]= EEPROM.read(32); } 
  }// no net end
  
  EEPROM.commit(); 
  
  delay(5000);

  if (Hours == AH1 && Min == AM1 && AV1 == 0) // for alarm1
    {
      alert1(); // Medicine alert
      for(int i = 0; i<sizeof(MS1) / sizeof(MS1[0]); i++)
      {
       W = MS1[i];
       work(); // medicine no.  
      }
      AV1=1;
      alert2(); // dont forget
    }

    else if (Hours == AH2 && Min == AM2 && AV2 == 0)
    {
      alert1();
      for(int i = 0; i<sizeof(MS2) / sizeof(MS2[0]); i++)
      {
        W = MS2[i];
       work();
      }
      AV2=1;
      alert2();
    }

   else if (Hours == AH3 && Min == AM3 && AV3 == 0)
    {
      alert1();
      for(int i = 0; i<sizeof(MS3) / sizeof(MS3[0]); i++)
      {
        W = MS3[i];
        work();
      }
      AV3=1;
      alert2();
    }

   else if(AV1!=0 || AV2!=0)
    {
      delay(30000);
      AV1=0; AV2=0; AV3=0;
    }

//_____________________________________________________day reset_______________________________________
    
//   if(Days != pDay)
//   {
//     AV1=0; AV2=0; AV3=0;
//     pDay=Days; 
//   }
   
   }// loop

 //__________________________________________void functions________________________________
 
void work()
{
  
  if (W == 0){}
  else if (W == 1)
  { 
  delay(1500);
  myStepper1.step(204.8);
  digitalWrite(D3,LOW);digitalWrite(D4,LOW);digitalWrite(D5,LOW);digitalWrite(D6,LOW);
  //delay(1000);
  //alarm(); 
  delay(5000); 
   }
   
  else if(W == 2)
  { 
   delay(1500);
   myStepper2.step(204.8);
   digitalWrite(D7,LOW);digitalWrite(D8,LOW);digitalWrite(3,LOW);digitalWrite(1,LOW);
   //alarm(); 
   delay(5000); 
   }
    
}

void work2()
{
  
  if (W == 0){}
  else if (W == 1)
  { 
   alarm(); delay(1500); 
  }
  else if(W == 2)
  { 
    alarm(); delay(1500); 
  }
   
}

void alert1()
{
  alarm();
  delay(2050);
  alarm(); // Tring Medicine Alert It's the time for
  delay(4050);
}

void alert2()
{
  alarm(); //don't forget to take your medicine 
  delay(5000);
  lm=millis();
}

void alarm(){
  tone(buzz,1000);
  delay(3000);
  noTone(buzz);
}
  
  
