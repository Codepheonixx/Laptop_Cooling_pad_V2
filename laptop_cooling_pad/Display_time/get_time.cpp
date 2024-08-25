#include "headers.h"

// Network credentials
const char *ssid     = "GODGIFTED";
const char *password = "ssgrp1234";

// Time offset in seconds for Indian Standard Time (UTC+5:30)
const short utcOffsetInSeconds = 19800;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds, 3600000); // Update every hour

unsigned long previousMillis = 0;
const long interval = 3600000; // Update time every hour (3600000 milliseconds)

// Arrays to day names
const char* daysOfWeek[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};


void get_wifi() {
  //This section connects to wifi
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_timR10_tr);
  u8g2.drawStr(23,20,"connecting to");
  u8g2.setFont(u8g2_font_t0_11_tr);
  u8g2.drawStr(36,36,ssid);
  u8g2.sendBuffer();

  short int counter = 0;

  WiFi.begin(ssid, password);
  u8g2.setCursor(12,50);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    if(counter >= 15){
      u8g2.setCursor(12,50);
      counter = 0;
    }
    u8g2.print(".");
    u8g2.sendBuffer();
    counter++;
  }
  u8g2.clearDisplay();
  
  u8g2.drawStr(36,36,"Connected");
  u8g2.sendBuffer();
  delay(3000);
  u8g2.clearDisplay();

}

void timeclient_update(){
  // Initialize the NTP client
  timeClient.begin();
  timeClient.update();
}

struct dateTime get_time() {

  unsigned long currentMillis = millis();

  // Update the time every hour
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    timeClient.update();
  }

  // Get epoch time
  unsigned long epochTime = timeClient.getEpochTime();
  
  struct dateTime dt;

  // Convert epoch time to time structure
  uint8_t currentHour = hour(epochTime);
  uint8_t currentMinute = minute(epochTime);
  uint8_t currentDay = day(epochTime);
  uint8_t currentMonth = month(epochTime);
  int currentYear = year(epochTime);
  uint8_t currentWeekDay = weekday(epochTime);

  // Convert to 12-hour format and determine AM/PM
  String period = "AM";
  if (currentHour == 0) {
    currentHour = 12; // Midnight is 12 AM
  } else if (currentHour == 12) {
    period = "PM"; // Noon is 12 PM
  } else if (currentHour > 12) {
    currentHour -= 12;
    period = "PM";
  }

  // Get month and day as strings
  const char* currentDayStr = daysOfWeek[currentWeekDay - 1];

  //print time
  snprintf(dt.Time, sizeof(dt.Time), "%02d:%02d", currentHour, currentMinute);

  //print date
  snprintf(dt.Date, sizeof(dt.Date), "%02d/%02d/%4d", currentDay, currentMonth, currentYear);

  //copies day to Day
  strncpy(dt.Day, currentDayStr, sizeof(dt.Day)); // Copy day name

  //copies period
  strncpy(dt.per, period.c_str(), sizeof(dt.per)); // Copy period

  return dt;
}


