#ifndef HEADERS_H
#define HEADERS_H

#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

//creating a structure to hold info
struct dateTime {
  char Time[7];
  char Date[12];
  char Day[11];
  char per[4];
};
  
void display_time();
void get_wifi();
void timeclient_update();
struct dateTime get_time();

#endif