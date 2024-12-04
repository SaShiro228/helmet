#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"
#include "FastLED.h"


#define LED_PIN 2
#define LED_NUM 50
#define LED_PIN1 3
#define LED_NUM1 50
#define LED_PIN2 13
#define LED_PIN3 2
#define LED_NUM23 50



CRGB leds[LED_NUM];
CRGB leds1[LED_NUM1];
CRGB leds2[LED_NUM23];
CRGB leds3[LED_NUM23];


MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  //mpu
  mpu.initialize();
  // состояние соединения
  Serial.println(mpu.testConnection() ? "MPU6050 OK" : "MPU6050 FAIL");
  delay(1000);

  //led
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, LED_NUM);
  FastLED.addLeds<WS2812, LED_PIN1, RGB>(leds1, LED_NUM1);
  FastLED.addLeds<WS2812, LED_PIN2, RGB>(leds2, LED_NUM23);
  FastLED.addLeds<WS2812, LED_PIN3, RGB>(leds3, LED_NUM23);
  FastLED.setBrightness(50);
}


void loop() {
  //mpu
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(ax); Serial.print('\t');
  Serial.print(ay); Serial.print('\t');
  Serial.print(az); Serial.print('\t');
  Serial.print(gx); Serial.print('\t');
  Serial.print(gy); Serial.print('\t');
  Serial.println(gz);
  delay(5);

  //led
  FastLED.clear();
  //led func

  FastLED.show();
  delay(30);
}


void right(bool flag){
  byte j =0;
  for(int i = 0; i < LED_NUM23; i++){
    leds2[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM23; i++){
      j = i + 3;
      if (j = LED_NUM23) i = LED_NUM23;
      leds2[i].setRGB(255, 255, 255);
      leds2[i+1].setRGB(255, 255, 255);
      leds2[i+2].setRGB(255, 255, 255);
      leds2[i+3].setRGB(255, 255, 255);
      leds2[i+5].setRGB(255, 255, 255);
    }
  }
}


void left(bool flag){
  byte j =0;
  for(int i = 0; i < LED_NUM23; i++){
    leds3[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM23; i++){
      j = i + 3;
      if (j = LED_NUM23) i = LED_NUM23;
      leds3[i].setRGB(255, 255, 255);
      leds3[i+1].setRGB(255, 255, 255);
      leds3[i+2].setRGB(255, 255, 255);
      leds3[i+3].setRGB(255, 255, 255);
      leds3[i+5].setRGB(255, 255, 255);
    }
  }
}


void stop(bool flag){
  byte j =0;
  for(int i = 0; i < LED_NUM1; i++){
    leds1[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM1; i++){
    leds1[i].setRGB(255, 0, 0);
  }
  }
}


void line(bool flag){
  byte j =0;
  for(int i = 0; i < LED_NUM; i++){
    leds[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM; i++){
    leds[i].setRGB(255, 0, 0);
  }
  }
}

