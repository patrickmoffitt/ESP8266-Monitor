/*
    Copyright (c) 2018 Patrick Moffitt

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

#ifndef MONITOR_MONITOR_OLED_DISPLAY_HPP
#define MONITOR_MONITOR_OLED_DISPLAY_HPP

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>
#include <Adafruit_FeatherOLED_WiFi.h>
#include <ESP8266WiFi.h>
#include "monitor_data.hpp"

#if defined(ESP8266)
#define BUTTON_A 12
#define BUTTON_B 13
#define BUTTON_C 14
#define LED      0
#endif

struct monitor_display {
    volatile int page{0};
    void enable();
    void disable();
    void show_page(int page);
    float map(long x, long in_min, long in_max, float out_min, float out_max);
    Adafruit_SSD1306 display = Adafruit_SSD1306();
    Adafruit_FeatherOLED_WiFi oled_wifi = Adafruit_FeatherOLED_WiFi();
};

#endif //MONITOR_MONITOR_OLED_DISPLAY_HPP
