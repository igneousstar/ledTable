#include <Wire.h>
#include "Sodaq_DS3231.h"

#include "FastLED.h"

#define NUM_LEDS 396  //how many leds are on the board
#define HORIZONTAL_LEDS 22 //leds in the vertical direction
#define VERTICAL_LEDS 18 //leds in the right direction

//rate of that the leds
//cycle through colors
//during rainbowTime()
#define HUEGRADE 15 

#define DATA_PIN 12 //data pins for leds

CRGB leds[NUM_LEDS]; //marix of led values


#define brightnessInt 19 //Interupt pin for brightness
#define brightnessUp 15 // brightness up button
#define brightnessDown 14 //brightness down button

#define moveInt 3 // move button interupt pin
#define moveUp 7 // up button
#define moveDown 5 // down button
#define moveLeft 4 // left button
#define moveRight 6 // right button

#define modeInt 2 // mode interupt
#define modeUp 8 // mode up button
#define modeDown 9 // mode down button

volatile int boardBrightness = 255; // Brightness of the board
volatile int mode = 1; //mode the table is on 

volatile int hue = 0; //color of the board
int mes = 0; // the month
int dia = 0; // the day
int hora = 0; // the hour
int minuto = 0; // the minutes
int segundo = 0; // the seconds
int segundoHue = 0; // a second color for the 

int right; // How far to move the hearts to the right
int up; // How far to move the hearts up
int a; // The color of the hearts 

/**
 * tells you the leds[] index based
 * on an x and y cordinate system
 * @param x, x cordinate
 * @param y, y cordinate
 * @return the index of the 
 * that matches the leds[] on the table
 */
 
int cords(int x, int y){
  int result;
  if(y%2 == 1)
  {
   result = ((y*HORIZONTAL_LEDS-1)-(x-1));
  }
  if(y%2 == 0)
  {
    result = (HORIZONTAL_LEDS*(y-1))+(x-1);
  }
  return result;
}

/**
 * These all write a character on the board. 
 * They include all of the alphabet, all numbers
 * and a heart. 
 * @param moveX, the x cordinate
 * @param moveY, the y cordinate
 * @param color, the color of the leds
 * @param saturation, the saturation of the leds
 * @param brightness, the brightness of the leds
 */
 
void A(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void B(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
}

void C(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void D(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void E(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
}

void f(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
}

void G(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
}

void H(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void I(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] =CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);

  leds[cords(3+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 4+moveY)] = CHSV(color, saturation, brightness);

  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void J(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void K(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] =CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
}

void L(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void M(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void N(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
}

void O(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void P(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void Q(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(2+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
}

void R(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
}

void S(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
}

void T(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void U(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void V(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void W(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void X(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void Y(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(3+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
}

void Z(int moveX, int moveY, int color, int saturation, int brightness){
  leds[cords(1+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 1+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(5+moveX, 5+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveX, 3+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveX, 2+moveY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveX, 4+moveY)] = CHSV(color, saturation, brightness);
}

void heart(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
    leds[cords(1+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(2+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(3+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(4+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(5+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(6+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(7+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(7+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(6+moveHeartX, 6+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(5+moveHeartX, 6+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(4+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(3+moveHeartX, 6+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(2+moveHeartX, 6+moveHeartY)] = CHSV(color, saturation, brightness);
    leds[cords(1+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
}

void one(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(4+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(4+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);

}

void two(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(1+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(2+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

}

void three(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(1+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

}

void four(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(4+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(1+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(2+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);

}

void five(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(1+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(4+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(1+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);

}

void six(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(1+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(1+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(2+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);

}

void seven(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(1+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(1+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

}

void eight(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(1+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  
  leds[cords(2+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);

}

void nine(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(2+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(2+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);

}

void zero(int moveHeartX, int moveHeartY, int color, int saturation, int brightness){
  leds[cords(1+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 1+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 2+moveHeartY)] = CHSV(color, saturation, brightness);

  leds[cords(4+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(3+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(2+moveHeartX, 5+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveHeartX, 4+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(1+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);
  leds[cords(4+moveHeartX, 3+moveHeartY)] = CHSV(color, saturation, brightness);

}

/**
 * writes a given of leds[] row on the table
 * with a specific color value
 * @param row, the row that you want to write
 * @param color, the color
 * @param saturation, the saturation
 * @param br, the brightness 
 */
 
void writeRow(int row, int color, int saturation, int br){
  leds[cords(1, row)] = color;
  for(int i=HORIZONTAL_LEDS; i > -1; i-=1)
  {
    leds[cords(i, row)] = CHSV( color, saturation, br);
    
  }
}

/**
 * Displays the time and date
 * from the real time clock
 */
 
void rainbowTime(){
  DateTime now = rtc.now();
  if(mes != now.month())
  {
    mes = now.month();
    for(int j=14; j<19; j++)
    {
      writeRow(j, 0, 0, 0);
    }
  }
  if(mes == 1)
  {
    J(3, 13, hue, 255, boardBrightness);
    A(8, 13, hue+HUEGRADE, 255, boardBrightness);
    N(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 2)
  {
    f(3, 13, hue, 255, boardBrightness);
    E(8, 13, hue+HUEGRADE, 255, boardBrightness);
    B(12, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 3)
  {
    M(3, 13, hue, 255, boardBrightness);
    A(8, 13, hue+HUEGRADE, 255, boardBrightness);
    R(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 4)
  {
    A(3, 13, hue, 255, boardBrightness);
    P(8, 13, hue+HUEGRADE, 255, boardBrightness);
    R(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 5)
  {
    M(3, 13, hue, 255, boardBrightness);
    A(8, 13, hue+HUEGRADE, 255, boardBrightness);
    Y(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 6)
  {
    J(1, 13, hue, 255, boardBrightness);
    U(6, 13, hue+HUEGRADE, 255, boardBrightness);
    N(11, 13, hue+(2*HUEGRADE), 255, boardBrightness);
    E(17, 13, hue+(3*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 7)
  {
    J(1, 13, hue, 255, boardBrightness);
    U(6, 13, hue+HUEGRADE, 255, boardBrightness);
    L(11, 13, hue+(2*HUEGRADE), 255, boardBrightness);
    Y(16, 13, hue+(3*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 8)
  {
    A(3, 13, hue, 255, boardBrightness);
    U(8, 13, hue+HUEGRADE, 255, boardBrightness);
    G(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 9)
  {
    S(3, 13, hue, 255, boardBrightness);
    E(8, 13, hue+HUEGRADE, 255, boardBrightness);
    P(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 10)
  {
    O(3, 13, hue, 255, boardBrightness);
    C(8, 13, hue+HUEGRADE, 255, boardBrightness);
    T(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 11)
  {
    N(3, 13, hue, 255, boardBrightness);
    O(8, 13, hue+HUEGRADE, 255, boardBrightness);
    V(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }
  else if(mes == 12)
  {
    D(3, 13, hue, 255, boardBrightness);
    E(8, 13, hue+HUEGRADE, 255, boardBrightness);
    C(13, 13, hue+(2*HUEGRADE), 255, boardBrightness);
  }

  if(dia != now.date())
  {
    dia = now.date();
    for(int j=9; j<14; j++)
    {
      writeRow(j, 0, 0, 0);
    }
  }
  if(dia/10 == 0)
  {
    zero(7, 8, hue, 255, boardBrightness);
    if(dia == 1)
    {
      one(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 2)
    {
      two(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 3)
    {
      three(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 4)
    {
      four(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 5)
    {
      five(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 6)
    {
      six(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 7)
    {
      seven(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 8)
    {
      eight(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia == 9)
    {
      nine(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
  }

  else if(dia/10 == 1)
  {
    one(7, 8, hue, 255, boardBrightness);
    if(dia%10 == 0)
    {
      zero(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 1)
    {
      one(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 2)
    {
      two(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 3)
    {
      three(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 4)
    {
      four(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 5)
    {
      five(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 6)
    {
      six(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 7)
    {
      seven(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 8)
    {
      eight(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 9)
    {
      nine(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }  
  }

  else if(dia/10 == 2)
  {
    two(7, 8, hue, 255, boardBrightness);
    if(dia%10 == 0)
    {
      zero(10, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 1)
    {
      one(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 2)
    {
      two(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 3)
    {
      three(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 4)
    {
      four(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 5)
    {
      five(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 6)
    {
      six(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 7)
    {
      seven(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 8)
    {
      eight(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else if(dia%10 == 9)
    {
      nine(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
  }
  else if(dia/10 == 3)
  {
    three(7, 8, hue, 255, boardBrightness);
    if(dia%10 == 0)
    {
      zero(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
    else
    {
      one(12, 8, hue+HUEGRADE, 255, boardBrightness);
    }
  }

  if(hora != now.hour())
  {
    hora = now.hour();
    for(int j=4; j<9; j++)
    {
      writeRow(j, 0, 0, 0);
    }
  }
  if(hora/10 == 0)
  {
    zero(1, 3, hue-HUEGRADE, 255, boardBrightness);
  }
  else if(hora/10 == 1)
  {
    one(1, 3, hue-HUEGRADE, 255, boardBrightness);
  }
  else if(hora/10 == 2)
  {
    two(1, 3, hue-HUEGRADE, 255, boardBrightness);
  }
  if(hora%10 == 0)
  {
    zero(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 1)
  {
    one(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 2)
  {
    two(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 3)
  {
    three(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 4)
  {
    four(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 5)
  {
    five(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 6)
  {
    six(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 7)
  {
    seven(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 8)
  {
    eight(6, 3, hue, 255, boardBrightness);
  }
  else if(hora%10 == 9)
  {
    nine(6, 3, hue, 255, boardBrightness);
  }


  if(minuto != now.minute())
  {
    minuto = now.minute();
    for(int j=4; j<9; j++)
    {
      writeRow(j, 0, 0, 0);
    }
  }
  if(minuto/10 == 0)
  {
    zero(13, 3, hue+HUEGRADE, 255, boardBrightness);
  }
  else if(minuto/10 == 1)
  {
    one(13, 3, hue+HUEGRADE, 255, boardBrightness);
  }
  else if(minuto/10 == 2)
  {
    two(13, 3, hue+HUEGRADE, 255, boardBrightness);
  }
  else if(minuto/10 == 3)
  {
    three(13, 3, hue+HUEGRADE, 255, boardBrightness);
  }
  else if(minuto/10 == 4)
  {
    four(13, 3, hue+HUEGRADE, 255, boardBrightness);
  }
  else if(minuto/10 == 5)
  {
    five(13, 3, hue+HUEGRADE, 255, boardBrightness);
  }


  if(minuto%10 == 0)
  {
    zero(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 1)
  {
    one(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 2)
  {
    two(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 3)
  {
    three(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 4)
  {
    four(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 5)
  {
    five(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 6)
  {
    six(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 7)
  {
    seven(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 8)
  {
    eight(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  else if(minuto%10 == 9)
  {
    nine(17, 3, hue+HUEGRADE*2, 255, boardBrightness);
  }
  //This is for seconds
  if(segundo != now.second())
  {
    segundo = now.second();
    if(segundo == 59)
    {
      for(int j=1; j<4; j++)
      {
        writeRow(j, 0, 0, 0);
      }
    }
    leds[segundo] = CHSV(segundoHue, 255, (boardBrightness/2));
    segundoHue += 10;
  }

 
  hue += 4;
  leds[cords(12, 5)] = CHSV(hue, 255, boardBrightness);
  leds[cords(12, 7)] = CHSV(hue, 255, boardBrightness);
}

/**
 * Cycles the brightness up
 * and down from 0 to max 
 */
 
void brightness() {
  static unsigned long brightness_interrupt_time = 0;
  unsigned long brightness_time = millis();
  // If interrupts come too fast, assume it's a bounce and ignore
  if (brightness_time - brightness_interrupt_time > 50)
  {
    if (digitalRead(brightnessUp) == HIGH && digitalRead(brightnessDown) == LOW) {
      boardBrightness += 10;
      if (boardBrightness > 255) {
        boardBrightness = 255;
      }
    }
    else {
      boardBrightness -= 10;
      if (boardBrightness < 0) {
        boardBrightness = 0;
      }
    }
  }
  brightness_interrupt_time = brightness_time;
}

/**
 * The direction that the snake is moving
 * Up is 0
 * Right is 1
 * Down is 2
 * Left is 3
 */
volatile int moveSnake = 1;

// Keeps track if the snake has already changed directions
volatile boolean moved = false;

int snakeX[395]; //snakeX positions
int snakeY[395]; //snakeY positions
int snakeSize = 3; //size of the snake

int applesX[3]; //apples to be eatens
int applesY[3];

/**
 * Changes the direction the snake is going if, and only 
 * if the snake has recently moved. It also updates the
 * value for hue. So, the color can be updated on the 
 * solid color mode. 
 */

void updateMove() {
  static unsigned long move_interrupt_time = 0;
  unsigned long move_time = millis();
  boolean up = digitalRead(moveUp);
  boolean down = digitalRead(moveDown);
  boolean left = digitalRead(moveLeft);
  boolean right = digitalRead(moveRight);
  // If interrupts come too fast, assume it's a bounce and ignore
  if (move_time - move_interrupt_time > 50 && moved == true)
  {
    hue = (hue + 3) % 255;
    if(moved && up && (moveSnake == 1 || moveSnake == 3)){
      moveSnake = 0;
    }
    if(moved && down && (moveSnake == 1 || moveSnake == 3)){
      moveSnake = 2;
    }
    if(moved && right && (moveSnake == 0 || moveSnake == 2)){
      moveSnake = 1;
    }
    if(moved && left && (moveSnake == 0 || moveSnake == 2)){
      moveSnake = 3;
    }
  move_interrupt_time = move_time;
 }
}


/*
* returns true if the indicated x and y
* are occupied by part of the snakes body
* returns false if not or if the cooridinates
* are the snakes head 
* @ return ture if occuppied 
*/

boolean isOccupied(int x, int y){
  for(int i = 1; i < snakeSize; i++){
    if(snakeX[i] == x && snakeY[i] == y){return true;}
  }
  return false;
}

/**
 * Checks to see if the snake's head comes
 * in contact with an apple. If it does, the 
 * apple is consumed and snakeSize 
 * increases by one. 
 */
 
void eatApple(){
  for(int i = 0; i < 3; i++){
    if(snakeX[0] == applesX[i] && snakeY[0] == applesY[i]){
      leds[cords(applesX[i], applesY[i])] = CHSV(0, 0, 0);
      applesX[i] = 0;
      snakeSize++;
    }
  }
}

/**
 * If one of the apples is eaten, 
 * A new apple will be randomly generated
 */
 
void makeApples(){
  for(int i = 0; i < 3; i++){
    if(applesX[i] == 0){

      // This loop keeps the apples from being generated
      // on top of the snakes's body
      while(applesX[i] == 0){
        applesX[i] = random(1, 23);
        applesY[i] = random(1, 19);
        if(isOccupied(applesX[i], applesY[i])){
          applesX[i] = 0;
        }
        else{
          leds[cords(applesX[i], applesY[i])] = CHSV(random(1, 256), 255, boardBrightness);
          LEDS.show();
        }
      }
    }
  }
}

/**
 * This updates the snakes position based upon
 * the way it is supposed to be moving. 
 */
 
void updateSnake(){
  leds[cords(snakeX[(snakeSize - 1)], snakeY[(snakeSize - 1)])] = CHSV(0, 0, 0);
  
  for(int i = snakeSize; i > 0; i -= 1){
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  if(moveSnake == 0){
    snakeY[0] = (snakeY[0] % 18) + 1;
  }
  else if(moveSnake == 1){
    snakeX[0] = (snakeX[0] % 22) + 1;
  }
  else if(moveSnake == 2){
    snakeY[0] -= 1; if(snakeY[0] < 1){snakeY[0] = 18;}
  }
  else if (moveSnake == 3){
    snakeX[0] -= 1; if(snakeX[0] < 1){snakeX[0] = 22;}
  }
  for(int i = 0; i < snakeSize; i++){
    leds[cords(snakeX[i], snakeY[i])] = CHSV(0, 255, boardBrightness);
  }
  LEDS.show();
}

/**
 * Checks to see if the snake should be dead.
 * If the snake is dead, resets snakeSize to 3
 */
 
void killSnake(){
  if(isOccupied(snakeX[0], snakeY[0]) && snakeSize > 3){
    for(int i = 0; i < snakeSize; i++){
      leds[cords(snakeX[i], snakeY[i])] = CHSV(0, 0, 0);
    }
    snakeSize = 3;
    LEDS.show();
  }
}

/**
 * Runs all of the methods involved in 
 * the snake game logic. 
 */

void snake() {
  eatApple();
  makeApples();
  updateSnake();
  killSnake();
  //The spead at which the snake moves
  delay(100);
  moved = true;
}

/**
 * Sets all the leds[] to 0
 */

void clearAll(){
  for(int i = 1; i < 19; i++){
      writeRow(i, 0, 0, 0);
    }
}

/**
 * Creates a rainbow of color that runs
 * from the top of the table to the botton
 */
 
void rainbowWave() {
  for(int j = 1; j<(VERTICAL_LEDS+1); j++)
  {
    writeRow(j, (hue+j*4), 255, boardBrightness);
  }
  FastLED.show();
  hue = hue+4;
  delay(50);
}

/**
 * Is meant to randomly place 
 * two hearts on the boad and then 
 * erase them. The hearts are 
 * valentine colors
 */

void valHearts() {

  // writes two hearts on the board
  // a is the color, a random red, blue or purple
  for(int i=0; i<2; i++)
  {
    a = random(98, 155);   
    right = random(0, 16);
    up = random(0, 13);
    heart(right, up, a, 255, boardBrightness);
  }
  FastLED.show();
  delay(500);
  //clear all of the LEDS 
  for(int i=0; i<395; i++)
  {
    leds[i] = 0;
  }
}


/**
 * Interupt that will run 
 * anytime the mode button 
 * is hit. Mode will cycle up 
 * and down. Values for mode range from 
 * 0 to 6
 */
 
void updateMode() {
  static unsigned long mode_interrupt_time = 0;
  unsigned long mode_time = millis();
  // If interrupts come too fast, assume it's a bounce and ignore
  if (mode_time - mode_interrupt_time > 200)
  {
    if (digitalRead(modeDown) == HIGH) {
      mode = (mode + 1) % 7;
    }
    else {
      mode -= 1; if (mode < 0) {
        mode = 6;
      }
    }
  }
  mode_interrupt_time = mode_time;
}

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(57600);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(15, INPUT);
  pinMode(14, INPUT);
  snakeX[0] = 12; //The starting coordinates for the snake
  snakeY[0] = 12;
  Wire.begin();
  rtc.begin();
  attachInterrupt(digitalPinToInterrupt(brightnessInt), brightness, RISING);
  attachInterrupt(digitalPinToInterrupt(moveInt), updateMove, RISING);
  attachInterrupt(digitalPinToInterrupt(modeInt), updateMode, HIGH);
}


void loop() {

  clearAll();

  // Displays the time and date
  // with a rainbow pattern 
  
  while(mode == 0)
  {
    rainbowTime();
    delay(25);
    FastLED.show();
  }

  while(mode == 1)
  {
    clearAll();
    FastLED.show();
  }

  clearAll();
 

  //Play the game snake
  //you need to redraw the apples
  //because they were all cleared before
  
  leds[cords(applesX[0], applesY[0])] = CHSV(random(0, 256), 255, boardBrightness);
  leds[cords(applesX[1], applesY[1])] = CHSV(random(0, 256), 255, boardBrightness);
  leds[cords(applesX[2], applesY[2])] = CHSV(random(0, 256), 255, boardBrightness);

  //Start playing snake :)
  while(mode == 2)
  {
    snake();
  }
  
  clearAll();

  // The mode for a wave of rainbows
  
  while(mode == 3)
  {
    rainbowWave();
  }

  clearAll();

  // The randomly moves two hearts on the board
  
  while(mode == 4)
  {
    valHearts();
  }
  clearAll();

  // Change brightness and color at will. 
  
  while(mode == 5)
  {
    for(int i = 1; i < 19; i++){
      writeRow(i, hue, 255, boardBrightness); //hue is a volatile veriable changed with the up arrows
    }
    delay(10); // Without this, bad things happen with the interputs. 
    FastLED.show();
  }
  
  clearAll();

  // Randomly blinks an LED
  // It makes it lookk ike the board is sparkling
  // with red, blue, and purple 
  // This is the dance party mode
  
  while(mode == 6){
  for(int i=0; i<1; i++)
  {
    leds[random(0, 395)] = random(0x1, 0xF0000);
  }
  FastLED.show();
  delay(1);
  for(int i=0; i<396; i++)
  {
    leds[i] = 0x0;
  }
  FastLED.show();
  }
}
