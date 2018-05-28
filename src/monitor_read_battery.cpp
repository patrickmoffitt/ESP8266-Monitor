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

#include "monitor_read_battery.hpp"

int get_battery_vdc() {
    // Read the battery level from the ESP8266 analog in pin.
    // Analog read level is 10 bit 0-1023 (0V-1V).
    // our 10MΩ & 2.2MΩ voltage divider takes the max
    // lipo value of 4.2V and drops it to 0.757V max.
    // this means our min analog read value should be 566 (3.14V)
    // and the max analog read value should be 757 (4.2V).
    const size_t readings_len{30};
    std::array<int, readings_len> readings;
    std::fill_n(begin(readings), readings_len, 0);
    for (int i=0; i < (int) readings_len; i++) {
        readings[i] = lround(analogRead(A0) * 0.97656) + MONITOR_READ_BATTERY_VDC_CALIBRATION;
        delay(33);
    }
    int sum = accumulate(begin(readings), end(readings), 0, std::plus<int>());
    int level = sum / readings_len;
    Serial.print("Raw ADC value: ");
    Serial.println(level);
    // convert battery level to percent
    level = map(level, 566, 757, 0, 100);
    Serial.print("Battery level: ");
    Serial.print(level);
    Serial.println("%");
    return level;
}