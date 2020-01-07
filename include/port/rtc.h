//
// Created by tia on 2020/01/07.
//

#ifndef TIEOS_RTC_H
#define TIEOS_RTC_H

#include <cstdint>


namespace rtc {

#pragma pack(1)

    struct DateTime {
        uint8_t yer;
        uint8_t mon;
        uint8_t day;
        uint8_t hor;
        uint8_t min;
        uint8_t sec;
        uint16_t __pack;
    };

    struct DateTimePack {
        uint8_t yerl :4;
        uint8_t yerh :4;
        uint8_t monl :4;
        uint8_t monh :4;
        uint8_t dayl :4;
        uint8_t dayh :4;
        uint8_t horl :4;
        uint8_t horh :4;
        uint8_t minl :4;
        uint8_t minh :4;
        uint8_t secl :4;
        uint8_t sech :4;
        uint16_t __pack;
    };

#pragma pack()

    DateTimePack get_time();

}

#endif //TIEOS_RTC_H
