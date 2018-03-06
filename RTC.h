/*
 *  Author:    Alberto Gil Tesa
 *  Website:   http://giltesa.com
 *  License:   CC BY-NC-SA 3.0
 *
 *  Project:   RTC_DS3231
 *  File:      RTC.h
 *  Date:      2018/03/06
 *  Version:   1.4.8
 */


#ifndef RTC_H_
#define RTC_H_

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif
#include "Wire.h"

#define RTC_ADDRESS 0x68
#define DST_OFF     0
#define DST_ON      1


/**
 * The secondary class, is used to return all data.
 */
class Data
{
  public:
    uint8_t  seconds;   //     0~59
    uint8_t  minutes;   //     0~59
    uint8_t  hour;      //     0~11
    uint8_t  hour24h;   //     0~23
    uint8_t  dayWeek;   //     0~6  (0=Sunday)
    uint8_t  day;       //     1~31
    uint8_t  month;     //     1~12
    uint16_t year;      //  2000~2099
    bool     dst;       //  true~false

    Data();
    Data( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes, uint8_t seconds );
    String toString();
    String toString( char* format );

    bool isAfter( Data after );
    bool isAfter( uint8_t hour24h, uint8_t minutes=0, uint8_t seconds=0 );
    bool isAfter( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes=0, uint8_t seconds=0 );

    bool isBefore( Data before );
    bool isBefore( uint8_t hour24h, uint8_t minutes=0, uint8_t seconds=0 );
    bool isBefore( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes=0, uint8_t seconds=0 );

    bool isBetween( Data after, Data before );
    bool isBetween( uint8_t a_hour24h, uint8_t b_hour24h );
    bool isBetween( uint8_t a_hour24h, uint8_t a_minutes, uint8_t b_hour24h, uint8_t b_minutes );
    bool isBetween( uint8_t a_hour24h, uint8_t a_minutes, uint8_t a_seconds, uint8_t b_hour24h, uint8_t b_minutes, uint8_t b_seconds );

    bool isBetween(  uint16_t a_year, uint8_t a_month, uint8_t a_day, uint8_t a_hour24h,
                     uint16_t b_year, uint8_t b_month, uint8_t b_day, uint8_t b_hour24h );

    bool isBetween( uint16_t a_year, uint8_t a_month, uint8_t a_day, uint8_t a_hour24h, uint8_t a_minutes,
                    uint16_t b_year, uint8_t b_month, uint8_t b_day, uint8_t b_hour24h, uint8_t b_minutes );

    bool isBetween( uint16_t a_year, uint8_t a_month, uint8_t a_day, uint8_t a_hour24h, uint8_t a_minutes, uint8_t a_seconds,
                    uint16_t b_year, uint8_t b_month, uint8_t b_day, uint8_t b_hour24h, uint8_t b_minutes, uint8_t b_seconds );
};



/**
 * The main class contains all methods to read or write
 * the time and date on the DS1307/DS3231 clock.
 */
class RTC
{
  public:
    RTC( bool DST );
    void setSeconds( uint8_t seconds );
    void setMinutes( uint8_t minutes );
    void setHour( uint8_t hour24h );
    void setTime( uint8_t hour24h, uint8_t minutes, uint8_t seconds );
    void setDay( uint8_t day );
    void setMonth( uint8_t  month );
    void setYear( uint16_t year );
    void setDate( uint16_t year, uint8_t month, uint8_t day );
    void setDateTime( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes, uint8_t seconds );
    Data getData();
    float getTemperature(); // DS3231 only!

private:
    bool onDST;
    bool estDST;
    uint8_t dayOnDST;
    uint8_t dayOffDST;
    void setDateTime( Data data );
    Data checkDST( Data data );
    uint16_t zeller( uint16_t year, uint8_t month, uint8_t day );
    uint8_t decToBcd(uint8_t val);
    uint8_t bcdToDec(uint8_t val);
};


#endif /* RTC_H_ */