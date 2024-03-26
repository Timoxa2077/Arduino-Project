#include "emg_reader.h"
#include <SoftwareSerial.h>

#define calib 1


#define led1 2
#define led2 4
#define led3 7
#define av_button 8
#define calib_button 9
#define pyezo A3
#define pot1 A5
#define pot2 A4
#define b_rx 13
#define b_tx 12

SoftwareSerial my_serial(b_tx,b_rx);

byte porog1 = 40;
byte porog2 = 40;

emg_reader er1(A0);
emg_reader er2(A1);

void auto_calib()
{
  long l_data_max = 0;
  long r_data_max = 0;
  long l_data_min = 0;
  long r_data_min = 0;
  
  //Serial.println("Расслабьте обе руки");
  digitalWrite(led1, HIGH);
  delay(1000);
  for(uint16_t i= 0; i <= 210; i++)
  {
    er1.step();
    er2.step();
    if(er1._ready)
    {
      l_data_min += er1.get_sData();
      r_data_min += er2.get_sData();
    }
    delay(5);
  }
  digitalWrite(led1, LOW);
  digitalWrite(led3, HIGH);
  //Serial.println("Напрягите левую руку");
  delay(1000);
  for(uint16_t i = 0; i <= 600; i++)
  {
    er1.step();
    if(er1._ready)
      l_data_max += er1.get_sData();
    delay(5);
  }
  //Serial.println("Расслабьте обе руки");
  digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH);
  //Serial.println("Напрягите правую руку");
  delay(1000);
  for(uint16_t i= 0; i <= 600; i++)
  {
    er1.step();
    if(er1._ready)
      r_data_max += er2.get_sData();
    delay(5);
  }
  //Serial.println("Расслабьте обе руки");
  digitalWrite(led2, LOW);
  l_data_min = l_data_min/20;
  r_data_min = r_data_min/20;
  l_data_max = l_data_max/20;
  r_data_max = r_data_max/20;

  porog1 = (l_data_max - l_data_min) / 2;
  porog2 = (r_data_max - r_data_min) / 2;
  //Serial.println("Калибровка завершена");
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(av_button, INPUT);
  pinMode(calib_button, INPUT);
  pinMode(b_tx, INPUT);
  pinMode(b_rx, OUTPUT);
  Serial.begin(9600);
  my_serial.begin(9600);
  Serial.println("porog_left porog_right sData_left sData_right");
}

double sData1 = 0;
double sData2 = 0;

bool potenc = 1;
byte jest = 0;

void loop() {
  if(potenc)
  {
    porog1 = analogRead(pot1)/4;
    porog2 = analogRead(pot2)/4;
  }
  er1.step();
  er2.step();
  if(er1._ready)
  {
    
    sData1 = er1.get_sData();
    sData2 = er2.get_sData();
    if(sData1 > porog1 && sData2 > porog2)
    {
      jest = 3;
      my_serial.write('3');
      #if !calib
        Serial.println('3');
      #endif
      for(uint16_t i= 0; i <= 600; i++)
      {
        er1.step();
        er2.step();
        delay(5);
        if(er1._ready)
        {
          er1.get_sData();
          er2.get_sData();
      }
  }
    }
    else if(sData1 > porog1)
    {
      jest = 1;
      #if !calib
        Serial.println('1');
      #endif
      my_serial.write('1');
    }
    else if(sData2 > porog2)
    {
      jest = 2;
      #if !calib
        Serial.println('2');
      #endif
      my_serial.write('2');
    }
  }
  if(digitalRead(av_button) && jest != 3)
  {
    my_serial.write('4');
    tone(A3, 700, 200);
    delay(4800);
    tone(A3, 700, 200);
    delay(4600);
    tone(A3, 700, 200);
    analogWrite(A3, 0);
  }
  if(digitalRead(calib_button) && potenc)
  {
    my_serial.write(8);
    auto_calib();
    my_serial.write(9);
    potenc = 0;
  }
  if(digitalRead(calib_button) && potenc == 0)
  {
    potenc = 1;
    while(digitalRead(calib_button));
    delay(100);
  }

  #if calib
    Serial.print(porog1);
    Serial.print(" ");
    Serial.print(porog2);
    Serial.print(" ");
    Serial.print(sData1);
    Serial.print(" ");
    Serial.println(sData2);
  #endif
  delay(15);
}
