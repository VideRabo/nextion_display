#include "Nextion.h"
#include <SoftwareSerial.h>

SoftwareSerial nextion(18, 19);
Nextion myNextion(nextion, 9600);

const int UART_BUFF_SIZE = 16;
char* buffer = new char[UART_BUFF_SIZE];
int buff_pos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(10, OUTPUT);
  
  myNextion.init();
  myNextion.setComponentValue("n0", 34);
}

void reset() {
  buff_pos = 0;  
}

void handle_input(char* buffer, int size) {
    Serial.print("IN DEC--> ");

    for(int i = 0; i < size; i+=4) {
      Serial.print(buffer[i], DEC);
      Serial.print(" ");  
    }

    int value = buffer[4];
    if(value!=0) {value*=4; value--;}
    analogWrite(10, value);

    Serial.println("<--");
    Serial.print("request, set n0 to ");
    Serial.println(value);
        
    Serial1.print("n0.val=");
    Serial1.print(value);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    
    
}

void loop() {
    
    if(Serial1.available()>0)
    {
        char c = Serial1.read();
        buffer[buff_pos++] = c;

        Serial.print(":");
        Serial.print(c, HEX);

        if( c == 0xFFFFFFFF )
        {
          Serial.println("");
          handle_input(buffer, buff_pos-1);
          Serial.print("buffer ");
          reset();
        }
    }
}
