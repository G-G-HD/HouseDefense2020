/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

int up;
int down;
int left;
int right;
//mem sono le variabili per esaminare lo stato
bool rmem;
bool umem;
bool dmem;
bool lmem;
String input;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(8,0);
  Serial.begin(9600);
}

void loop(){
  LCD();
}


void serialEvent(){
  input = Serial.readString();
  serialCommandLcd();
}

void serialCommandLcd(){
  if(input=="up\n"){
    if(umem==true){
      up=0;
    }else if (umem==false){
      up=1;
    }
     umem=!(umem);
  }

    if(input=="down\n"){
    if(umem==true){
      down=0;
    }else if (dmem==false){
      down=1;
    }
     dmem=!(dmem);
  }

    if(input=="left\n"){
    if(lmem==true){
      left=0;
    }else if (lmem==false){
      down=1;
    }
     lmem=!(lmem);
  }

    if(input=="right\n"){
    if(rmem==true){
      right=0;
    }else if (rmem==false){
      right=1;
    }
     rmem=!(rmem);
  }
}

void LCD(){
  if (up==1){
    lcd.setCursor(3,0);
    lcd.print("^");
  }else{
    lcd.setCursor(3,0);
    lcd.print(" ");
  }
  if (down==1){
    lcd.setCursor(3,1);
    lcd.print("v");
  }else{
    lcd.setCursor(3,1);
    lcd.print(" ");
  }
  if (left==1){
    lcd.setCursor(0,0);
    lcd.print("<");
  }else{
    lcd.setCursor(0,0);
    lcd.print(" ");
  }
  if (right==1){
    lcd.setCursor(1,0);
    lcd.print(">");
  }else{
    lcd.setCursor(1,0);
    lcd.print(" ");
  }
  //if(laser==HIGH){
    //lcd.setCursor(10,0);
    //lcd.print("---*");
  //}else{
    //lcd.setCursor(10,0);
    //lcd.print("    ");
  //}
}
