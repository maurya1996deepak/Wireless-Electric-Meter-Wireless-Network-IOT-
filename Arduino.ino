#include <SoftwareSerial.h>
#define RX 10
#define TX 11
String AP = "deepak";       // CHANGE ME
String PASS = "22222222"; // CHANGE ME
String Mn = "75";   // CHANGE ME
String HOST = "192.168.43.31";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
SoftwareSerial esp8266(RX,TX); 
#include "ACS712.h"
char watt[5];
ACS712 sensor(ACS712_20A, A0);
unsigned long last_time =0;
unsigned long current_time =0;
float Wh =0 ;  

 
  
void setup() {
 
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
  sensor.calibrate();
  
}

void loop() {
  float V = 230;
  float I = sensor.getCurrentAC();
  if(I<=0.06)
  {
    I=0.00;
    }
  Serial.println(I);
  float P = V * I;
  last_time = current_time;
  current_time = millis();    
  Wh = Wh+  P *(( current_time -last_time) /3600000.0) ; 
   dtostrf(Wh, 4, 2, watt);   
   Serial.println(watt);     
 String getData = "GET /energy?mn="+ Mn +"&"+ field +"="+String(watt);
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,5,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 Serial.println(getData);
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime-3))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
