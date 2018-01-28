/*
 * pin 11 is connected to the DataIn 
 * pin 13 is connected to the CLK 
 * pin  9 is connected to LOAD 
 * **** Please set the number of devices you have *****
 */

#include "LedControlExt.h"
#include <OneWire.h>

LedControlExt lc=LedControlExt(11, 13, 9, 4);


OneWire ds(10);

byte addr[8]={0x28,0xFF,0x98,0xA5,0x64,0x15,0x01,0x9F};
// 28 FF 98 A5 64 15 1 9F

volatile int celsius;
int oldT = 0;

void setup() {
  Serial.begin(115200);
  pinMode (13,OUTPUT);
  WDTCSR=(1<<WDCE)|(1<<WDE);		//установить биты WDCE WDE (что б разрешить запись в другие биты
  WDTCSR=(1<<WDIE)| (1<<WDP2)|(1<<WDP1);// разрешение прерывания + выдержка 1 секунда
  
  ds.reset(); 				// сброс шины
  ds.select(addr); 			// выставить адрес
  ds.write(0x4E);			// разрешение записать конфиг
  ds.write(0x7F);			// Th контроль температуры макс 128грд
  ds.write(0xFF);			// Tl контроль температуры мин -128грд
  ds.write(0x20); 			// 0x60 12-бит разрешение, 0x00 -9бит разрешение; 0x20 - 10bit
}


void loop() { 
  if (celsius != oldT) {
    Serial.print("Temperature = ");
    Serial.println(celsius/16.0);
    lc.printString("+" + String(round(celsius/16.0)), 0);
    oldT = celsius;
  }
  
}



ISR (WDT_vect){ 	//вектор прерывания WD
  static boolean n=0;	// флаг работы: запрос температуры или её чтение
  n=!n;
  digitalWrite(13, n);
  if (n) {
    ds.reset(); 	// сброс шины
    ds.select(addr);	// выбор адреса
    ds.write(0x44);	// начать преобразование (без паразитного питания)
  } else {
    ds.reset();
    ds.select(addr);
    ds.write(0xBE);	// Read Scratchpad (чтение регистров) &nbsp;
    celsius = ds.read() | (ds.read()<<8); //прочитаны 2 байта&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;
  }
}


