#include "headers.h"

void setup(){

  Serial.begin(115200);
  u8g2.begin();

  //connects to wifi
  get_wifi();

  //Initalize the client
  timeclient_update();

}

void loop(){

  display_time();

}