using namespace std;
#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"
#include "FastLED.h"
#include "BluetoothSerial.h"

#define LED_PIN 12
#define LED_NUM 23
#define LED_PIN1 13
#define LED_NUM1 10
#define LED_PIN2 4
#define LED_PIN3 14
#define LED_NUM23 13

BluetoothSerial ESP_BT;

CRGB leds[LED_NUM];
CRGB leds1[LED_NUM1];
CRGB leds2[LED_NUM23];
CRGB leds3[LED_NUM23];

int mp[6];


MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
bool flag1;

String get_data();
int transform_data(String data);
void off_all();
void stop(bool flag);
void line(bool flag);
void left(bool flag);
void right(bool flag);

void setup() {
 
  ESP_BT.begin("Helmet");
  Serial.println("Bluetooth Device is Ready to Pair");
 

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
  // for(int i = 0; i < 3; i++){
  //   ESP_BT.print(mp[i]); ESP_BT.print("\t");
  //   Serial.print(mp[i]); Serial.print("\t");
  // }
  //Serial.println(mp[1]);
  // ESP_BT.println("");
  


  //led
  //led func
  String data = get_data();
  Serial.println(data);
  int daat = data.toInt();
  if(daat == 1){
    Serial.println("off");
    off_all();
    flag1 = false;
  } if(daat == 2){
    FastLED.clear();
    Serial.println("on");
    flag1 = true;
  } 
  if(flag1){
    stop(false);
    left(false);
    line(false);
    right(false);
    if(mp[1] > 30){
      left(true);
    } else if(mp[1] < -30){
      right(true);
    }
  }
  FastLED.show();
  int sd = mp[1];
  ESP_BT.print(sd);
}


void right(bool flag){
  for(int i = 0; i < LED_NUM23; i++){
    leds3[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM23; i++){
      leds3[i].setRGB(255, 255, 0);
    }
  }
}


void left(bool flag){
  for(int i = 0; i < LED_NUM23; i++){
    leds2[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM23; i++){
      leds2[i].setRGB(255, 255, 0);
    }
  }
}


void stop(bool flag){
    FastLED.clear();
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
  for(int i = 0; i < LED_NUM; i++){
    leds[i].setRGB(255, 255, 255);
  }
  if(flag){
    for(int i = 0; i < LED_NUM; i++){
    leds[i].setRGB(0, 255, 0);
  }
  }
}

String get_data(){
  if (ESP_BT.available()){
    String data;
    data = ESP_BT.readString();
    return data;
  }
}


void off_all(){
    FastLED.clear();
  for(int i = 0; i < LED_NUM; i++){
    leds[i].setRGB(0, 0, 0);
  }
  for(int i = 0; i < LED_NUM1; i++){
    leds1[i].setRGB(0, 0, 0);
  }
  for(int i = 0; i < LED_NUM23; i++){
    leds2[i].setRGB(0, 0, 0);
  }
  for(int i = 0; i < LED_NUM23; i++){
    leds3[i].setRGB(0, 0, 0);
  }
}

