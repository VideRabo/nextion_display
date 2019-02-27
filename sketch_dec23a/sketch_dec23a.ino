#include "Nextion.h"
#include <SoftwareSerial.h>

SoftwareSerial nextion(18, 19);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

void setup() {
  // put your setup code here, to run once:  
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("Serial Initiated!");
  myNextion.init(); // send the initialization commands for Page 0
}
 
void loop() {
 int val = myNextion.getComponentValue("h0");
 String message = myNextion.listen();
 if(message != "") {
  Serial.println(message);
 }
 myNextion.setComponentValue("n0", val);
  
  
}
