#ifndef OLED_H
#define OLED_H
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

bool initOLED();

void updateOLED();

void showSplash();

#endif