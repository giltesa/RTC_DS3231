/*
 *  Author:    Alberto Gil Tesa
 *  Website:   http://giltesa.com
 *  License:   CC BY-NC-SA 3.0
 *
 *  Project:   RTC_DS3231
 *  File:      ex5_clock_print_to_string.ino
 *  Date:      2018/03/06
 */


#include <Wire.h>
#include <RTC.h>

RTC rtc(DST_ON);


void setup()
{
    Serial.begin(9600);
    while(!Serial);
    delay(1000);
}



void loop()
{
    Data d = rtc.getData();

    // GET DATE AND TIME, Format: 2014/10/15 01:40:41
    //Serial.println( d.toString() );


    // GET DATA PREFORMATTED:
    // VALUE =  DESCRIPTION
    //   Y   =  Year of 2000 to 2099
    //   y   =  Year of 00 to 99
    //   m   =  Month of 01 to 12
    //   n   =  Month of 1 to 12
    //   w   =  DayWeek of 0 to 6 (0=Sunday)
    //   W   =  DayWeek of 1 to 7 (7=Sunday)
    //   d   =  Day of 01 to 31
    //   j   =  Day of 1 to 31
    //   H   =  Hour of 00 to 23
    //   h   =  Hour of 00 to 11
    //   G   =  Day of 0 to 23
    //   g   =  Day of 0 to 11
    //   i   =  Minutes of 00 to 59
    //   s   =  Seconds of 00 to 59
    Serial.println( d.toString("Y-m-d H:i:s") );

    delay(1000);
}