#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <EEPROM.h>
#include <NewPing.h>
SSD1306AsciiWire oled;

NewPing sonarf(3, 3, 30);
NewPing sonarl(2, 2, 30);
NewPing sonarr(4, 4, 30);

#define left_motor_forward 6
#define left_motor_backward 7
#define right_motor_forward 8
#define right_motor_backward 9
#define left_motor_speed 5
#define right_motor_speed 11

#define btn1 10// শর্ট প্রেস: UP, লং প্রেস: SELECT
#define btn2 12 // শর্ট প্রেস: DOWN, লং প্রেস: BACK
#define led 13



int speed, error, spl, spr, turn_speed;
int brake_time, turn_brake, turn90_delay, node_delay, stop_timer, u_turn_timer, i_timer;
int obstacle_distance, wall_distance, wall_mid, wallp, wall_limit = 25;
char side = 'r', turn = 's', cross = 's';
int pos;

int sensor, sum;
int s[6], base[6] = { 1, 2, 4, 8, 16, 32 };
int threshold[6], maximum[6], minimum[6];
bool i_mode = 0;
int sf, sl, sr;

byte path[25] = { 1, 14 };
byte memory = 50;
int counter;

uint32_t m1, m2, tf, tr, tl;


void setup() {
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  eeprom_refresh();
  path_load();
  Veloxa();
}

void loop() {
  byte r1 = push(btn1);
  if (r1 == 2) { 
    menu(); // শুধু এটি কল করলেই কাজ করবে
    Veloxa(); // মেনু থেকে পুরোপুরি বের হলে লোগো দেখাবে
  }
}
