#ifndef DATETIME_H
#define DATETIME_H

/*
    DateTime library for C++ wrapping the linux time_t
    as a class.

    Mozilla Public License 2.0

    Author Matt Saint-Gregory DEC 2021
*/

#include <ctime>
#include <iostream>
#include <cstring>
#include <sstream>

// indent -as -nut -ts4 -bli0 -i4 -blf -nbfda -npsl -c0 -cd0 -nip -nlp -nprs -npcs -ncs -nsaf -nsai -nsaw  -l120 

struct ymdhns
{
    int yy;
    int mm;
    int dd;
    int hh;
    int nn;
    int ss;
};

const int SecondsPerMinute = 60;
const int SecondsPerHour = 3600;
const int SecondsPerDay = 86400;

const int DaysOfMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const std::string DaysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

const std::string MonthsOfYear[] = { "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

typedef void (*funcfromstring)(const std::string datetimestring, ymdhns & decoded);
typedef void (*functostring)(const int year,const int month,const int day, const int hour, const int minute,const int second);

class datetime
{
  private:

    time_t value = 0;

    void decode(const time_t dt, ymdhns & decoded);
    time_t encode(const ymdhns & toencode);

  public:

    datetime() {}
    datetime(const std::string createstring);
    datetime(const std::string createstring, funcfromstring func);
    datetime(const time_t init);  
    datetime(const datetime &other) : value(other.value) {} // copy constructor    
    datetime(datetime&& other) : value(std::move(other.value)) {} // move constructor

    // copy
    datetime& operator=(const datetime& other);

    // move
	datetime& operator=(const datetime&& other);


    virtual ~datetime() {}

    // comparison operators
    bool operator ==(const datetime& other) const;
    bool operator <(const datetime& other) const;
    bool operator >(const datetime& other) const;
	bool operator >=(const datetime& other) const;
	bool operator <=(const datetime& other) const;
	bool operator !=(const datetime& other) const;
    
    // add and sub operators
	datetime& operator+ (const datetime& other);	
	datetime& operator+= (const datetime& other);	
	datetime& operator- (const datetime& other);
	datetime& operator-= (const datetime& other);
	


    void now();
    void yesterday();
    void tomorrow();
    void midnight();
    void noon();
    void janfirst(int year = 0);
    void setfirstdayofmonth();
    void setlastdayofmonth();


    std::string tostring();
    std::string tostring(functostring func);
    void fromstring(const std::string datetimestring);
    void fromstring(const std::string datetimestring, funcfromstring func); // with lambda adapter

    void setdatetime(const int year, const int month, const int day, const int hour,
        const int minute, const int second);
    void setdate(const int year, const int month, const int day);
    void settime(const int hour, const int minute, const int second);

    int dayofweek() const;
    std::string dayofweekstring()const;
    int dayofyear() const;
    int weekofyear() const;

    void addseconds(int count = 1);
    void addminutes(int count = 1);
    void addhours(int count = 1);
    void adddays(int count = 1);
    
    bool isleapyear();

    bool samedatetime(const datetime & other);
    bool samedate(const datetime & other);
    bool sametime(const datetime & other);
    bool samehour(const datetime & other);
    bool sameminute(const datetime & other);
    bool samesecond(const datetime & other);

    int secondsapart(const datetime & other);
    int minutesapart(const datetime & other);
    int hoursapart(const datetime & other);
    int daysapart(const datetime & other);

    void difference(const datetime & other, int &days, int &hours, int &minutes, int &seconds);

    int secondsaftermindnight();
    int minutesaftermindnight();

    int year();
    int month();
    std::string monthstr();
    std::string daystr();
    int day();
    int hour();
    int minute();
    int second();

    bool issunday();
    bool ismonday();
    bool istuesday();
    bool iswednesday();
    bool isthursday();
    bool isfriday();
    bool issaturday();

    time_t get() const;
    void set(time_t tt);
};

#endif

