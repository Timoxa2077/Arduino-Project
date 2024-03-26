#include "jests.h"
#include "my_servo.h"
#include <SoftwareSerial.h>

SoftwareSerial my_serial(A1, A0);

void setup() {
  s_attach();
  jest0();
  my_serial.begin(9600);
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A0, OUTPUT);
}

void loop() {
  if(my_serial.available())
  {
    char c = my_serial.read();
    Serial.println(c);
    if(c == '1')
      jest1();
    else if(c == '2')
      jest2();
    else if(c == '3')
      jest3();
    else if(c == '4')
      av_otcl();
  }
  
}
