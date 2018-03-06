/*
 *  Author:    Alberto Gil Tesa
 *  Website:   http://giltesa.com
 *  License:   CC BY-NC-SA 3.0
 *
 *  Project:   RTC_DS3231
 *  File:      RTC.cpp
 *  Date:      2016/03/24
 *  Version:   1.4.7
 */


#include "RTC.h"
#include <string.h>


/**
 * The secondary class, is used to return all data.
 */
Data::Data()
{

}
Data::Data( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes, uint8_t seconds )
{
	this->year    = year;
	this->month   = month;
	this->day     = day;
	this->hour24h = hour24h;
	this->minutes = minutes;
	this->seconds = seconds;
}



/**
 * Returns the clock data in this format: 2014/10/15 1:40:41
 *
 * @return A String with the data clock.
 */
String Data::toString()
{
    String s = String(year);
    s.concat("/");
    s.concat(month);
    s.concat("/");
    s.concat(day);
    s.concat(" ");

    if( hour24h < 10 )
        s.concat("0");
    s.concat(hour24h);
    s.concat(":");

    if( minutes < 10 )
        s.concat("0");
    s.concat(minutes);
    s.concat(":");

    if( seconds < 10 )
        s.concat("0");
    s.concat(seconds);

    return s;
}



/**
 * Returns the clock data in specified format.
 *
 * VALUE = DESCRIPTION
 *   Y   = Year    of 2000 to 2099
 *   y   = Year    of   00 to 99
 *   m   = Month   of   01 to 12
 *   n   = Month   of    1 to 12
 *   d   = Day     of   01 to 31
 *   j   = Day     of    1 to 31
 *   H   = Hour    of   00 to 23
 *   h   = Hour    of   00 to 11
 *   G   = Day     of    0 to 23
 *   g   = Day     of    0 to 11
 *   i   = Minutes of   00 to 59
 *   s   = Seconds of   00 to 59
 *
 *   Example: "Y-m-d H:i:s" == "2014-10-15 1:40:41"
 *   Example: "Ymd"         == "20141015"
 *
 * @param format: Array of characters with the output format.
 * @return A String with the data clock.
 */
String Data::toString(char* format)
{
    int length = String(format).length();
    String s = String("");

    for( int i=0 ; i<length ; i++ )
    {
        switch( format[i] )
        {
            // Year of 2000 to 2099
            case 'Y':
                s.concat(year);
                break;

            // Year of 00 to 99
            case 'y':
                s.concat(year-2000);
                break;

            // Month of 01 to 12
            case 'm':
                if( month < 10 )
                    s.concat("0");
                s.concat(month);
                break;

            // Month of 1 to 12
            case 'n':
                s.concat(month);
                break;

            // Day of 01 to 31
            case 'd':
                if( day < 10 )
                    s.concat("0");
                s.concat(day);
                break;

            // Day of 1 to 31
            case 'j':
                s.concat(day);
                break;

            // Hour of 00 to 23
            case 'H':
                if( hour24h < 10 )
                    s.concat("0");
                s.concat(hour24h);
                break;

            // Hour of 00 to 11
            case 'h':
                if( hour < 10 )
                    s.concat("0");
                s.concat(hour);
                break;

            // Day of 0 to 23
            case 'G':
                s.concat(hour24h);
                break;

            // Day of 0 to 11
            case 'g':
                s.concat(hour);
                break;

            // Minutes of 00 to 59
            case 'i':
                if( minutes < 10 )
                    s.concat("0");
                s.concat(minutes);
                break;

            // Seconds of 00 to 59
            case 's':
                if( seconds < 10 )
                    s.concat("0");
                s.concat(seconds);
                break;

            default:
                s.concat(format[i]);
                break;
        }
    }

    return s;
}



/**
 * This method tests if this time is after the specified time.
 */
bool Data::isAfter( Data after )
{
    if( year > after.year )
    {
        return true;
    }
    else if( year == after.year )
    {
        if( month > after.month )
        {
           return true;
        }
        else if( month == after.month )
        {
            if( day > after.day )
            {
                return true;
            }
            else if( day == after.day )
            {
                if( hour24h > after.hour24h )
                {
                    return true;
                }
                else if( hour24h == after.hour24h )
                {
                    if( minutes > after.minutes )
                    {
                        return true;
                    }
                    else if( minutes == after.minutes  )
                    {
                        if( seconds > after.seconds )
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
bool Data::isAfter( uint8_t hour24h, uint8_t minutes, uint8_t seconds )
{
	return isAfter( this->year, this->month, this->day, hour24h, minutes, seconds );
}
bool Data::isAfter( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes, uint8_t seconds )
{
	Data a = Data( year, month, day, hour24h, minutes, seconds );
	return isAfter(a);
}



/**
 * This method tests if this time is before the specified time.
 */
bool Data::isBefore( Data before )
{
    if( year < before.year )
    {
        return true;
    }
    else if( year == before.year )
    {
        if( month < before.month )
        {
           return true;
        }
        else if( month == before.month )
        {
            if( day < before.day )
            {
                return true;
            }
            else if( day == before.day )
            {
                if( hour24h < before.hour24h )
                {
                    return true;
                }
                else if( hour24h == before.hour24h )
                {
                    if( minutes < before.minutes )
                    {
                        return true;
                    }
                    else if( minutes == before.minutes  )
                    {
                        if( seconds < before.seconds )
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
bool Data::isBefore( uint8_t hour24h, uint8_t minutes, uint8_t seconds )
{
	return isBefore( this->year, this->month, this->day, hour24h, minutes, seconds );
}
bool Data::isBefore( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes, uint8_t seconds )
{
	Data b = Data( year, month, day, hour24h, minutes, seconds );
	return isBefore(b);
}



/**
 * This method tests if this time is between the specified times.
 */
bool Data::isBetween( Data after, Data before )
{
    return isAfter(after) && isBefore(before);
}
bool Data::isBetween( uint8_t a_hour24h, uint8_t b_hour24h )
{
    return isBetween(this->year, this->month, this->day, a_hour24h, 0, 0, this->year, this->month, this->day, b_hour24h, 0, 0 );
}
bool Data::isBetween( uint8_t a_hour24h, uint8_t a_minutes, uint8_t b_hour24h, uint8_t b_minutes )
{
    return isBetween(this->year, this->month, this->day, a_hour24h, a_minutes, 0, this->year, this->month, this->day, b_hour24h, b_minutes, 0 );
}
bool Data::isBetween( uint8_t a_hour24h, uint8_t a_minutes, uint8_t a_seconds, uint8_t b_hour24h, uint8_t b_minutes, uint8_t b_seconds )
{
    return isBetween(this->year, this->month, this->day, a_hour24h, a_minutes, a_seconds, this->year, this->month, this->day, b_hour24h, b_minutes, b_seconds);
}
bool Data::isBetween( uint16_t a_year, uint8_t a_month, uint8_t a_day, uint8_t a_hour24h, uint16_t b_year, uint8_t b_month, uint8_t b_day, uint8_t b_hour24h )
{
	return isBetween(a_year, a_month, a_day, a_hour24h, 0, 0, b_year, b_month, b_day, b_hour24h, 0, 0);
}
bool Data::isBetween( uint16_t a_year, uint8_t a_month, uint8_t a_day, uint8_t a_hour24h, uint8_t a_minutes, uint16_t b_year, uint8_t b_month, uint8_t b_day, uint8_t b_hour24h, uint8_t b_minutes )
{
	return isBetween(a_year, a_month, a_day, a_hour24h, a_minutes, 0, b_year, b_month, b_day, b_hour24h, b_minutes, 0);
}
bool Data::isBetween( uint16_t a_year, uint8_t a_month, uint8_t a_day, uint8_t a_hour24h, uint8_t a_minutes, uint8_t a_seconds, uint16_t b_year, uint8_t b_month, uint8_t b_day, uint8_t b_hour24h, uint8_t b_minutes, uint8_t b_seconds )
{
	Data a = Data( a_year, a_month, a_day, a_hour24h, a_minutes, a_seconds );
	Data b = Data( b_year, b_month, b_day, b_hour24h, b_minutes, b_seconds );
	return isBetween(a, b);
}



/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/



/**
 * The main class contains all methods to read or write
 * the time and date on the DS1307/DS3231 clock.
 *
 * @param DST: Boolean that enables the automatic time change summer/winter.
 */
RTC::RTC( bool DST )
{
    Wire.begin();

    onDST     = DST;
    estDST    = false;
    dayOnDST  = 0;
    dayOffDST = 0;
}



/**
 * Sets the seconds of the clock.
 * @param seconds: unsigned byte
 */
void RTC::setSeconds( uint8_t seconds )
{
    Data data = this->getData();
    data.seconds = seconds;
    this->setDateTime(data);
}



/**
 * Sets the minutes of the clock.
 * @param minutes: unsigned byte
 */
void RTC::setMinutes( uint8_t minutes )
{
    Data data = this->getData();
    data.minutes = minutes;
    this->setDateTime(data);
}



/**
 * Sets the hour24h of the clock.
 * @param hour24h: unsigned byte
 */
void RTC::setHour( uint8_t hour24h )
{
    Data data = this->getData();
    data.hour24h = hour24h;
    this->setDateTime(data);
}



/**
 * Sets the hour24h, minutes and seconds of the clock.
 * @param hour24h: unsigned byte
 * @param minutes: unsigned byte
 * @param seconds: unsigned byte
 */
void RTC::setTime( uint8_t hour24h, uint8_t minutes, uint8_t seconds )
{
    Data data = this->getData();
    data.hour24h = hour24h;
    data.minutes = minutes;
    data.seconds = seconds;
    this->setDateTime(data);
}



/**
 * Sets the day of the clock.
 * @param day: unsigned byte
 */
void RTC::setDay( uint8_t day )
{
    Data data = this->getData();
    data.day = day;
    data.dayWeek = zeller( data.year, data.month, data.day );
    data.dayWeek = (data.dayWeek == 0 ? 7 : data.dayWeek);
    this->setDateTime(data);
}



/**
 * Sets the month of the clock.
 * @param month: unsigned byte
 */
void RTC::setMonth( uint8_t  month )
{
    Data data = this->getData();
    data.month = month;
    this->setDateTime(data);
}



/**
 * Sets the year of the clock.
 * @param year: unsigned int
 */
void RTC::setYear( uint16_t year )
{
    Data data = this->getData();
    data.year = year;
    this->setDateTime(data);
}



/**
 * Sets the year, month and day of the clock.
 * @param year: unsigned int
 * @param month: unsigned byte
 * @param day: unsigned byte
 */
void RTC::setDate( uint16_t year, uint8_t month, uint8_t day )
{
    Data data = this->getData();
    data.year = year;
    data.month = month;
    data.day = day;
    data.dayWeek = zeller( data.year, data.month, data.day );
    data.dayWeek = (data.dayWeek == 0 ? 7 : data.dayWeek);
    this->setDateTime(data);
}



/**
 * Sets the year, month, day, hour24h, minutes, seconds of the clock.
 * @param year: unsigned int
 * @param month: unsigned byte
 * @param day: unsigned byte
 * @param hour24h: unsigned byte
 * @param minutes: unsigned byte
 * @param seconds: unsigned byte
 */
void RTC::setDateTime( uint16_t year, uint8_t month, uint8_t day, uint8_t hour24h, uint8_t minutes, uint8_t seconds )
{
    Data data = this->getData();
    data.year = year;
    data.month = month;
    data.day = day;
    data.dayWeek = zeller( data.year, data.month, data.day );
    data.dayWeek = (data.dayWeek == 0 ? 7 : data.dayWeek);
    data.hour24h = hour24h;
    data.minutes = minutes;
    data.seconds = seconds;
    this->setDateTime(data);
}



/**
 * Returns a Data object with all the data clock.
 *
 * @return Data Object
 */
Data RTC::getData()
{
    Wire.beginTransmission(RTC_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(0);
    #else
        Wire.send(0);
    #endif
    Wire.endTransmission();
    Wire.requestFrom(RTC_ADDRESS, 7);

    Data data;

    #if ARDUINO >= 100
        data.seconds    = bcdToDec(Wire.read() & 0x7f);
        data.minutes    = bcdToDec(Wire.read());
        data.hour24h    = bcdToDec(Wire.read() & 0x3f);
        data.hour       = (data.hour24h > 12) ? data.hour24h - 12 : data.hour24h;
        data.dayWeek    = bcdToDec(Wire.read());
        data.day        = bcdToDec(Wire.read());
        data.month      = bcdToDec(Wire.read());
        data.year       = bcdToDec(Wire.read()) + 2000;
    #else
        data.seconds    = bcdToDec(Wire.receive() & 0x7f);
        data.minutes    = bcdToDec(Wire.receive());
        data.hour24h    = bcdToDec(Wire.receive() & 0x3f);
        data.hour       = (data.hour24h > 12) ? data.hour24h - 12 : data.hour24h;
        data.dayWeek    = bcdToDec(Wire.receive());
        data.day        = bcdToDec(Wire.receive());
        data.month      = bcdToDec(Wire.receive());
        data.year       = bcdToDec(Wire.receive()) + 2000;
    #endif

    return this->checkDST(data);
}



/**
 * Returns the temperature only in the DS3231 clock
 * @return float
 */
float RTC::getTemperature()
{
    byte temperature;

    Wire.beginTransmission(RTC_ADDRESS);
    #if ARDUINO >= 100
        Wire.write(uint8_t(0x11));
    #else
        Wire.send(uint8_t(0x11));
    #endif
    Wire.endTransmission();
    Wire.requestFrom(RTC_ADDRESS, 2);

    #if ARDUINO >= 100
        temperature = Wire.read();
    #else
        temperature = Wire.receive();
    #endif

    return float(temperature) + 0.25*(Wire.read()>>6);
}



/* PRIVATE */



void RTC::setDateTime( Data d )
{
    Data old = this->getData();

    Wire.beginTransmission(RTC_ADDRESS);

    #if ARDUINO >= 100
        Wire.write(0);
        Wire.write(decToBcd( (d.seconds >= 0 && d.seconds <= 59) ? d.seconds : old.seconds ));
        Wire.write(decToBcd( (d.minutes >= 0 && d.minutes <= 59) ? d.minutes : old.minutes ));
        Wire.write(decToBcd( (d.hour24h >= 0 && d.hour24h <= 23) ? d.hour24h : old.hour24h ));
        Wire.write(decToBcd( (d.dayWeek >= 1 && d.dayWeek <= 7 ) ? d.dayWeek : old.dayWeek ));
        Wire.write(decToBcd( (d.day     >= 1 && d.day     <= 31) ? d.day     : old.day     ));
        Wire.write(decToBcd( (d.month   >= 1 && d.month   <= 12) ? d.month   : old.month   ));

        if( d.year >= 0  &&  d.year <= 99 )
            Wire.write(decToBcd(d.year));
        else if( d.year >= 2000  &&  d.year <= 2099 )
            Wire.write(decToBcd(d.year-2000));
        else
            Wire.write(decToBcd(old.year));
    #else
        Wire.send(0);
        Wire.send(decToBcd( (d.seconds >= 0 && d.seconds <= 59) ? d.seconds : old.seconds ));
        Wire.send(decToBcd( (d.minutes >= 0 && d.minutes <= 59) ? d.minutes : old.minutes ));
        Wire.send(decToBcd( (d.hour24h >= 0 && d.hour24h <= 23) ? d.hour24h : old.hour24h ));
        Wire.send(decToBcd( (d.dayWeek >= 1 && d.dayWeek <= 7 ) ? d.dayWeek : old.dayWeek ));
        Wire.send(decToBcd( (d.day     >= 1 && d.day     <= 31) ? d.day     : old.day     ));
        Wire.send(decToBcd( (d.month   >= 1 && d.month   <= 12) ? d.month   : old.month   ));

        if( d.year >= 0  &&  d.year <= 99 )
            Wire.send(decToBcd(d.year));
        else if( d.year >= 2000  &&  d.year <= 2099 )
            Wire.send(decToBcd(d.year-2000));
        else
            Wire.send(decToBcd(old.year));
    #endif

    Wire.endTransmission();
}



Data RTC::checkDST( Data data )
{
    if( onDST )
    {
        if( dayOnDST == 0 || dayOffDST == 0 )
        {
            dayOnDST  = 31 - zeller( (data.month <= 3  ? data.year : data.year+1),  3, 31 );
            dayOffDST = 31 - zeller( (data.month <= 10 ? data.year : data.year+1), 10, 31 );
            estDST       = ((data.month == 3 && data.day >= dayOnDST && data.hour24h > 2) || data.month==4 || data.month==5 || data.month==6 || data.month==7 || data.month==8 || data.month==9 || (data.month == 10 && data.day <= dayOffDST && data.hour24h < 3)) ? true : false;
        }

        if( !estDST  &&  data.month == 3  &&  data.day == dayOnDST  &&  data.hour24h == 2 )
        {
            data.hour24h++;
            estDST = true;
            dayOnDST  = 31 - zeller( data.year+1, 3, 31 );
            this->setDateTime(data);
        }
        else if( estDST  &&  data.month == 10  &&  data.day == dayOffDST  &&  data.hour24h == 3 )
        {
            data.hour24h--;
            estDST = false;
            dayOffDST = 31 - zeller( data.year+1, 10, 31 );
            this->setDateTime(data);
        }
    }

    data.dst = estDST;
    return data;
}



uint16_t RTC::zeller( uint16_t year, uint8_t month, uint8_t day )
{
    if( month > 2 )
        month -= 2;
    else
    {
        month += 10;
        year -= 1;
    }

    int a = year % 100;
    int b = year / 100;
    return (700 + ((26 * month - 2) / 10) + day + a + a / 4 + b / 4 - 2 * b) % 7;
}



uint8_t RTC::decToBcd(uint8_t dec)
{
  return( (dec/10*16) + (dec%10) );
}



uint8_t RTC::bcdToDec(uint8_t bcd)
{
  return( (bcd/16*10) + (bcd%16) );
}