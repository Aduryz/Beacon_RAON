#include <SoftwareSerial.h>
 
SoftwareSerial BSerial(2, 3); //TX to 2, RX to 3

String val;
int RSSI_boundary = -65;
char location;

String pink;
String pinkR; //RSSI
int pR;
int headP;  //parsing
int tailP;
int headPR;
int tailPR;
int pinkP = 0;
String orange;
String orangeR;
int oR;
int headO;
int tailO;
int headOR;
int tailOR;
int orangeP = 0;
String yellow;
String yellowR;
int yR;
int headY;
int tailY;
int headYR;
int tailYR;
int yellowP = 0;

void setup()  {
  Serial.begin(9600);
  Serial.println("Hello!");
  BSerial.begin(9600);
}
 
void loop(){
  if (tailOR - headOR == 0){
    scan_and_parsing();
  }
  else{
    Serial.print("location: ");
    Serial.println(location);
    delay(40);
    exit(0);
  }
}

void scan_and_parsing(){
  delay(10);  // 꼭 있어야함
  BSerial.println("AT+SCAN"); //beacon scan

  if (BSerial.available()){
    String val = BSerial.readString();
    Serial.print("I received: ");
    Serial.println(val);  //beacon scan value
    delay(50);

    while(orangeP==0){
      headO = val.indexOf("74:F0:7D:1A:02:A5");
      while (tailO < headO){
       tailO = val.indexOf("]", tailO+1);
      } 
      orange = val.substring(headO, tailO);

      while (headOR<tailO){
        headOR = val.indexOf("RSSI", headOR+1);
      }
      while (tailOR < headOR){
        tailOR = val.indexOf("]", tailOR+1);
      }
      orangeR = val.substring(headOR+5, tailOR);

      Serial.print("orangeR: ");
      Serial.println(orangeR);
      if (orange=="74:F0:7D:1A:02:A5"){
        orangeP = 1;
      }
      delay(10);
      break;
    }
   
    pR = pinkR.toInt();
    oR = orangeR.toInt();
    yR = yellowR.toInt();
    if(pR>RSSI_boundary && oR<RSSI_boundary && yR<RSSI_boundary){  //locantion tracking
      location = 'A';
    }
    else if(pR<RSSI_boundary && oR>RSSI_boundary && yR<RSSI_boundary){
      location = 'B';
    }
    else if(pR<RSSI_boundary && oR<RSSI_boundary && yR>RSSI_boundary){
      location = 'C';
    }
    else if(pR>RSSI_boundary && oR>RSSI_boundary && yR<RSSI_boundary){
      location = 'D';
    }
    else if(pR>RSSI_boundary && oR<RSSI_boundary && yR>RSSI_boundary){
      location = 'E';
    }
    else if(pR<RSSI_boundary && oR>RSSI_boundary && yR>RSSI_boundary){
      location = 'F';
    }
    else if(pR>RSSI_boundary && oR>RSSI_boundary && yR>RSSI_boundary){
      location = 'G';
    }
    else{
      location = 'U';
    }
  }
}
