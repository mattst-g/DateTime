/*
    DateTime library for C++ wrapping the linux time_t
    as a class.

    Mozilla Public License 2.0

    Author Matt Saint-Gregory DEC 2021
*/

#include "datetime.h"


// Private function
// unpacks a time_t to a structure
void datetime::decode(const time_t dt, ymdhns & decoded)
{
    const tm *t = localtime(&dt);
    decoded.yy = t->tm_year + 1900;
    decoded.mm = t->tm_mon + 1;
    decoded.dd = t->tm_mday;
    decoded.hh = t->tm_hour;
    decoded.nn = t->tm_min;
    decoded.ss = t->tm_sec;
}

// Private function
// Packs a structure containing time components into a time_t
time_t datetime::encode(const ymdhns & toencode)
{
    tm whenStart;
    whenStart.tm_year = toencode.yy - 1900;
    whenStart.tm_mon = toencode.mm - 1;
    whenStart.tm_mday = toencode.dd;
    whenStart.tm_hour = toencode.hh;
    whenStart.tm_min = toencode.nn;
    whenStart.tm_sec = toencode.ss;
    whenStart.tm_isdst = -1;
    return mktime(&whenStart);
}

// sets the value to now
void datetime::now()
{
    value = time(nullptr);
}


// sets the value to yesterday date but 
// maintains the time portion
void datetime::yesterday()
{
    ymdhns currenttime;
    decode(value, currenttime);

    time_t temp = time(nullptr);
    temp -= SecondsPerDay;

    ymdhns newdate;
    decode(temp, newdate);

    newdate.hh = currenttime.hh;
    newdate.nn = currenttime.nn;
    newdate.ss = currenttime.ss;

    value = encode(newdate);
}

// sets the value to tomorrow date but
// maintains the time portion 
void datetime::tomorrow()
{
    ymdhns currenttime;
    decode(value, currenttime);

    time_t temp = time(nullptr);
    temp += SecondsPerDay;

    ymdhns newdate;
    decode(temp, newdate);

    newdate.hh = currenttime.hh;
    newdate.nn = currenttime.nn;
    newdate.ss = currenttime.ss;

    value = encode(newdate);
}


// sets the time to midnight leaving the date unchanged
void datetime::midnight()
{
    ymdhns currenttime;
    decode(value, currenttime);

    currenttime.hh = 0;
    currenttime.nn = 0;
    currenttime.ss = 0;

    value = encode(currenttime);
}

// sets the time to midday leaving the date unchanged
void datetime::noon()
{
    ymdhns currenttime;
    decode(value, currenttime);

    currenttime.hh = 12;
    currenttime.nn = 0;
    currenttime.ss = 0;

    value = encode(currenttime);
}


// sets the month and day to JAN 1 leaving the current
// year and time unchanged
void datetime::janfirst(int year)
{
    ymdhns currenttime;
    decode(value, currenttime);

    currenttime.mm = 1;
    currenttime.dd = 1;
    if(year > 0)
        currenttime.yy = year;

    value = encode(currenttime);
}


// returns the day of week the current value
// represents in the range 0..6 with Sunday as first day
int datetime::dayofweek() const
{
    const tm *t = localtime(&value);
    return t->tm_wday;
}

// returns the day of week as a string
std::string datetime::dayofweekstring()const
{
    const tm *t = localtime(&value);
    return DaysOfWeek[t->tm_wday];
}

// returns the nth day of the year that the date represents
int datetime::dayofyear() const
{
    const tm *t = localtime(&value);
    return t->tm_yday + 1;
}

// returns the week number 0..51 that the date represents
int datetime::weekofyear() const
{
    const int DAYS_PER_WEEK = 7;
    const tm *t = localtime(&value);
    const int wday = t->tm_wday;
    const int delta = wday ? wday - 1 : DAYS_PER_WEEK - 1;

    return (t->tm_yday + DAYS_PER_WEEK - delta) / DAYS_PER_WEEK;
}

// adds or subtracts a second or seconds
// the default value is to add 1 second, 
// Changing the default to a negative value subtracts
void datetime::addseconds(int count)
{
    value += count;
}

// adds or subtracts a minute or minute
// the default value is to add 1 minute, 
// Changing the default to a negative value subtracts
void datetime::addminutes(int count)
{
    value = value + (SecondsPerMinute * count);
}

// adds or subtracts a hours or hours
// the default value is to add 1 hours, 
// Changing the default to a negative value subtracts
void datetime::addhours(int count)
{
    value = value + (SecondsPerHour * count);
}

// adds or subtracts a day or daye
// the default value is to add 1 day, 
// Changing the default to a negative value subtracts
void datetime::adddays(int count)
{
    value = value + (SecondsPerDay * count);
}

// Returns a formatted string in line with linux ctime format
// it is coded here so that alternative formats can be used
std::string datetime::tostring()
{
    std::stringstream ss;
    ymdhns currenttime;
    decode(value, currenttime);

    ss << DaysOfWeek[dayofweek()].substr(0, 3) << " ";
    ss << MonthsOfYear[currenttime.mm - 1].substr(0, 3) << " ";
    if(currenttime.dd < 10)
        ss << ' ';
    ss << currenttime.dd << " ";
    if(currenttime.hh < 10)
        ss << '0';
    ss << currenttime.hh;
    ss << ':';
    if(currenttime.nn < 10)
        ss << '0';
    ss << currenttime.nn;
    ss << ':';
    if(currenttime.ss < 10)
        ss << '0';
    ss << currenttime.ss;
    ss << " " << currenttime.yy;

    return ss.str();
}


// Decodes a linux format string with the format
// Wed Dec 29 20:28:23 2021
void datetime::fromstring(const std::string datetimestring)
{
    ymdhns currenttime;
    currenttime.mm = 0;
    tm whenStart;

    char dstr[16];
    char mstr[16];

    
    sscanf(datetimestring.c_str(), "%s %s %d %d:%d:%d %d", dstr, mstr,
        &currenttime.dd, &currenttime.hh, &currenttime.nn, &currenttime.ss, &currenttime.yy);

    for(int idx = 0; idx < 12; ++idx)
    {
        if(strncmp(mstr, MonthsOfYear[idx].c_str(), 3) == 0)
        {
            currenttime.mm = idx;
            break;
        }
    }

    whenStart.tm_year = currenttime.yy - 1900;
    whenStart.tm_mon = currenttime.mm;
    whenStart.tm_mday = currenttime.dd;
    whenStart.tm_hour = currenttime.hh;
    whenStart.tm_min = currenttime.nn;
    whenStart.tm_sec = currenttime.ss;
    whenStart.tm_isdst = -1;

    value = mktime(&whenStart);
}

// Decodes a none linux format string 
// makes a call to function / lambda to parse the datetime values
void datetime::fromstring(const std::string datetimestring, funcfromstring func)
{
    if(func != nullptr)
    {
        ymdhns result;
        func(datetimestring, result);
        value = encode(result);
    }
}


// Sets all components of the date time as individual values
void datetime::setdatetime(const int year, const int month, const int day,
    const int hour, const int minute, const int second)
{
    ymdhns currenttime;
    currenttime.yy = year;
    currenttime.mm = month;
    currenttime.dd = day;
    currenttime.hh = hour;
    currenttime.nn = minute;
    currenttime.ss = second;
    value = encode(currenttime);
}

// sets only the date portion of the current value
void datetime::setdate(const int year, const int month, const int day)
{
    ymdhns currenttime;
    decode(value, currenttime);
    currenttime.yy = year;
    currenttime.mm = month;
    currenttime.dd = day;
    value = encode(currenttime);
}

// sets only the time portion of the current value
void datetime::settime(const int hour, const int minute, const int second)
{
    ymdhns currenttime;
    decode(value, currenttime);
    currenttime.hh = hour;
    currenttime.nn = minute;
    currenttime.ss = second;
    value = encode(currenttime);
}

// sets the date to the 1st day of the month that the date value holds
void datetime::setfirstdayofmonth()
{
    ymdhns currenttime;
    decode(value, currenttime);
    currenttime.dd = 1;
    value = encode(currenttime);
}

// sets the date to the last day of the month that the date value holds
void datetime::setlastdayofmonth()
{
    ymdhns currenttime;
    decode(value, currenttime);
    if(currenttime.mm == 1 && isleapyear())
    {
        currenttime.dd = DaysOfMonth[currenttime.mm] + 1;
    }
    else
    {
        currenttime.dd = DaysOfMonth[currenttime.mm];
    }
    value = encode(currenttime);
}

// returns true if the year component is a leap year
bool datetime::isleapyear()
{
    ymdhns currenttime;
    decode(value, currenttime);
    if(currenttime.yy % 4 != 0)
    {
        return false;
    }
    
    if(currenttime.yy % 100 != 0)
    {
        return true;
    }
    return (currenttime.yy % 400) == 0;
}

// returns only the year number
int datetime::year()
{
    ymdhns currenttime;
    decode(value, currenttime);
    return currenttime.yy;
}

// returns only the month number
int datetime::month()
{
    ymdhns currenttime;
    decode(value, currenttime);
    return currenttime.mm;
}

// returns the month as a string
std::string datetime::monthstr()
{
    ymdhns currenttime;
    decode(value, currenttime);
    return MonthsOfYear[currenttime.mm - 1];
}

// returns the day as a string
std::string datetime::daystr()
{
    int d = dayofweek();
    return DaysOfWeek[d];
}

// returns only the day number
int datetime::day()
{
    ymdhns currenttime;
    decode(value, currenttime);
    return currenttime.dd;
}


// returns only the hour number
int datetime::hour()
{
    ymdhns currenttime;
    decode(value, currenttime);
    return currenttime.hh;
}

// returns only the minute number
int datetime::minute()
{
    ymdhns currenttime;
    decode(value, currenttime);
    return currenttime.nn;
}

// returns only the seconds number
int datetime::second()
{
    ymdhns currenttime;
    decode(value, currenttime);
    return currenttime.ss;
}

// returns true if date value is a sunday
bool datetime::issunday()
{
    int d = dayofweek();
    return d == 0;
}

// returns true if date value is a monday
bool datetime::ismonday()
{
    int d = dayofweek();
    return d == 1;
}

// returns true if date value is a tuesday
bool datetime::istuesday()
{
    int d = dayofweek();
    return d == 2;
}

// returns true if date value is a wednesday
bool datetime::iswednesday()
{
    int d = dayofweek();
    return d == 3;
}

// returns true if date value is a thursday
bool datetime::isthursday()
{
    int d = dayofweek();
    return d == 4;
}

// returns true if date value is a friday
bool datetime::isfriday()
{
    int d = dayofweek();
    return d == 5;
}

// returns true if date value is a saturday
bool datetime::issaturday()
{
    int d = dayofweek();
    return d == 6;
}

// returns true this and another datetime the same
bool datetime::samedatetime(const datetime & other)
{
    return other.value == value;
}

// returns true if this and another date are the same
// ignores the time components
bool datetime::samedate(const datetime & other)
{
    ymdhns currenttime1;
    ymdhns currenttime2;
    decode(value, currenttime1);
    decode(other.value, currenttime2);

    return ((currenttime1.yy == currenttime2.yy)
        && (currenttime1.mm == currenttime2.mm) && (currenttime1.dd == currenttime2.dd));
}

// returns true if this and another time are the same
// ignores the date components
bool datetime::sametime(const datetime & other)
{
    ymdhns currenttime1;
    ymdhns currenttime2;
    decode(value, currenttime1);
    decode(other.value, currenttime2);

    return ((currenttime1.hh == currenttime2.hh)
        && (currenttime1.nn == currenttime2.nn) && (currenttime1.ss == currenttime2.ss));
}

// returns true if this and another hours are the same
// ignores all other parts of the datetime
bool datetime::samehour(const datetime & other)
{
    ymdhns currenttime1;
    ymdhns currenttime2;
    decode(value, currenttime1);
    decode(other.value, currenttime2);

    return (currenttime1.hh == currenttime2.hh);
}

// returns true if this and another minutes are the same
// ignores all other parts of the datetime
bool datetime::sameminute(const datetime & other)
{
    ymdhns currenttime1;
    ymdhns currenttime2;
    decode(value, currenttime1);
    decode(other.value, currenttime2);

    return (currenttime1.nn == currenttime2.nn);
}

// returns true if this and another seconds are the same
// ignores all other parts of the datetime
bool datetime::samesecond(const datetime & other)
{
    ymdhns currenttime1;
    ymdhns currenttime2;
    decode(value, currenttime1);
    decode(other.value, currenttime2);

    return (currenttime1.ss == currenttime2.ss);
}


// returns the difference with this and another time in seconds
int datetime::secondsapart(const datetime & other)
{
    return other.value - value;
}

// returns the difference with this and another time in minutes
int datetime::minutesapart(const datetime & other)
{
    int v = other.value - value;

    return v != 0 ? (v / SecondsPerMinute) : 0;
}

// returns the difference with this and another time in hours
int datetime::hoursapart(const datetime & other)
{
    int v = other.value - value;

    return v != 0 ? v / SecondsPerHour : 0;
}

// returns the difference with this and another time in days
int datetime::daysapart(const datetime & other)
{
    int v = other.value - value;

    return v != 0 ? v / SecondsPerDay : 0;
}

// returns the difference with this and another time in days, hours, minutes and seconds
void datetime::difference(const datetime & other, int &days, int &hours, int &minutes, int &seconds)
{
    int sec = abs(int (other.value - value));

    days = 0;
    minutes = 0;
    hours = 0;
    seconds = 0;

    if(sec >= SecondsPerDay)
    {
        days = sec / SecondsPerDay;
        sec = sec - (days * SecondsPerDay); // remainder in sec
    }

    if(sec >= SecondsPerHour)
    {
        hours = sec / SecondsPerHour;
        sec = sec - (hours * SecondsPerHour);   // remainder in sec 
    }

    if(sec >= SecondsPerMinute)
    {
        minutes = sec / SecondsPerMinute;
        sec = sec - (minutes * SecondsPerMinute);   // remainder in sec 
    }

    seconds = sec;
}
