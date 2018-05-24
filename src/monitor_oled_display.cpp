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

#include "monitor_oled_display.hpp"
extern monitor_data sensor;
extern ESP8266WiFiClass WiFi;
extern bool degrees_c_f;

void monitor_display::enable() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize I2C address 0x3C.
    display.clearDisplay();
    display.display();
}

void monitor_display::disable() {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
}

void monitor_display::show_page(int page) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    oled_wifi.init();
    oled_wifi.clearDisplay();
    oled_wifi.clearMsgArea();
    oled_wifi.setBatteryVisible(false);
    oled_wifi.setBatteryIcon(false);
    oled_wifi.renderBattery();
    oled_wifi.setConnectedVisible(false);
    oled_wifi.setRSSIVisible(false);
    oled_wifi.setIPAddressVisible(false);
    oled_wifi.refreshIcons();

    display.display();

    switch (page) {
        default:
        case 0 : {
            char date_time[21];
            memcpy(&date_time, &sensor.unix_epoch_time[4], sizeof(date_time));
            display.println(date_time);
            if (degrees_c_f) {
                double temperature_c = (sensor.temperature_f - 32.0) * (5.0 / 9.0);
                display.print(temperature_c);
                display.println(" C");
            } else {
                display.print(sensor.temperature_f);
                display.println(" F");
            }
            display.print(sensor.humidity_rh);
            display.println(" rH");
            display.print(sensor.current_ma);
            display.println(" mA");
            break;
        }
        case 1 : {
            float voltage;
            voltage = map(sensor.battery_vdc, 0, 100, 3.14, 4.20);
            if (voltage >= 3.15) {
                oled_wifi.setBattery(voltage);
                oled_wifi.setBatteryVisible(true);
                oled_wifi.setBatteryIcon(true);
                oled_wifi.renderBattery();
            }
            bool wifi_connect_status = WiFi.isConnected();
            if (wifi_connect_status){
                oled_wifi.setConnected(wifi_connect_status);
                oled_wifi.setConnectedVisible(true);
                int32_t rssi = WiFi.RSSI();
                uint32_t ipAddress = WiFi.localIP();
                oled_wifi.setRSSI(rssi);
                oled_wifi.setRSSIVisible(true);
                oled_wifi.setIPAddress(ipAddress);
                oled_wifi.setIPAddressVisible(true);
                oled_wifi.setConnected(true);
                oled_wifi.setConnectedVisible(true);
            }
            oled_wifi.refreshIcons();
            break;
        }
        case 2 : {
            display.print("ID: ");
            display.println(AIO_GROUP_KEY);

            display.print(ESP.getSdkVersion());
            display.print(" ");
            display.println(ESP.getCoreVersion());

            display.print("S U/F ");
            display.print(ESP.getSketchSize());
            display.print("/");
            display.println(ESP.getFreeSketchSpace());

            display.print("Free Heap: ");
            display.println(ESP.getFreeHeap());

            break;
        }
    }
    display.setCursor(0,0);
    display.display();
}

float monitor_display::map(long x, long in_min, long in_max, float out_min, float out_max) {
    long divisor = (in_max - in_min);
    if(divisor == 0){
        return -1; //AVR returns -1, SAM returns 0
    }
    return (x - in_min) * (out_max - out_min) / divisor + out_min;
}