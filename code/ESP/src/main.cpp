#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"
#include "FastLED.h"


#define LED_PIN 12
#define LED_NUM 23
#define LED_PIN1 13
#define LED_NUM1 10
#define LED_PIN2 4
#define LED_PIN3 14
#define LED_NUM23 13



CRGB leds[LED_NUM];
CRGB leds1[LED_NUM1];
CRGB leds2[LED_NUM23];
CRGB leds3[LED_NUM23];
int mp[6];


MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void stop(bool flag);
void line(bool flag);
void left(bool flag);
void right(bool flag);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //mpu
  mpu.initialize();
  // состояние соединения
  Serial.println(mpu.testConnection() ? "MPU6050 OK" : "MPU6050 FAIL");
  FastLED.setMaxPowerInVoltsAndMilliamps(3.3, 500);
  

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
  mp[0] = ax/160;
  mp[1] = ay/160;
  mp[2] = az/160;
  mp[3] = gx;
  mp[4] = gy;
  mp[5] = gz;
  delay(5);
  Serial.print(mp[0]); Serial.print('\t');
  Serial.print(mp[1]); Serial.print('\t');
  Serial.print(mp[2]); Serial.print('\t');
  Serial.print(mp[3]); Serial.print('\t');
  Serial.print(mp[4]); Serial.print('\t');
  Serial.println(mp[5]); 

  //led
  //led func
  //stop(true);
  // left(true);
  // line(true);
  // for(int i = 0; i < LED_NUM; i++){
  //   leds[i].setRGB(255, 255, 255);
  // }
  // for(int i = 0; i < LED_NUM1; i++){
  //   leds1[i].setRGB(255, 255, 255);
  // }
  // for(int i = 0; i < LED_NUM23; i++){
  //   leds2[i].setRGB(255, 255, 255);
  // }
  // for(int i = 0; i < LED_NUM23; i++){
  //   leds3[i].setRGB(255, 255, 255);
  // }
  delay(100);
  if (mp[1] > 30){
    for(int i = 0; i < LED_NUM23; i++){
      leds2[i].setRGB(255, 255, 0);
    }
  }else if(mp[1] < -30){
    for(int i = 0; i < LED_NUM23; i++){
      leds3[i].setRGB(255, 255, 0);
    }
  }else{
    for(int i = 0; i < LED_NUM23; i++){
      leds2[i].setRGB(255, 255, 255);
    }
    for(int i = 0; i < LED_NUM23; i++){
      leds3[i].setRGB(255, 255, 255);
    }
  }
    if (mp[0] < -50){
      stop(true);
      line(true);
  }else{
    stop(false);
    line(false);
  }
  FastLED.show();
}


void right(bool flag){
  byte j =0;
  FastLED.clear();
  for(int i = 0; i < LED_NUM23; i++){
    leds2[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM23; i++){
      leds2[i].setRGB(0, 255, 255);
    }
    FastLED.show();
    // delay(1000);
    for(int i = 0; i < LED_NUM23; i++){
      leds2[i].setRGB(0, 255, 255);
    }
    FastLED.show();
  }
}


void left(bool flag){
  byte j =0;
  for(int i = 0; i < LED_NUM23; i++){
    //leds2[i].setRGB(0, 0, 0);
    leds2[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM23; i++){
      leds2[i].setRGB(255, 255, 255);
    }
    //delay(1000);
    for(int i = 0; i < LED_NUM23; i++){
      leds2[i].setRGB(0, 0, 0);
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
    leds1[i].setRGB(0, 255, 0);
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
    leds[i].setRGB(0, 255, 0);
  }
  }
}

