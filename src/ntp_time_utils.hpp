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

#ifndef MONITOR_NTP_TIME_UTILS_HPP
#define MONITOR_NTP_TIME_UTILS_HPP

#include <Arduino.h>
#include <ctime>
#include <map>
#include <cstring>
#include "monitor_data.hpp"

struct ntp_time_utils {
    static const std::map<int, std::pair<int, int>> dst_dates;
    void set_dst_usa(tm *time_o, time_t *time_stamp);
    char EASTERN_TIMEZONE_ABBREV[5] = " EST";
    void set_time_of_day();
    int dst_offset_seconds{0};
};

#endif //MONITOR_NTP_TIME_UTILS_HPP
