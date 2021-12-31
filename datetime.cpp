#include "datetime.h"



void datetime::decode(const time_t dt, ymdhns &decoded)
{
	const tm * t = localtime(&dt);
	decoded.yy = t->tm_year;
	decoded.mm = t->tm_mon;
	decoded.dd = t->tm_mday;
	decoded.hh = t->tm_hour;
	decoded.nn = t->tm_min;
	decoded.ss = t->tm_sec;
}

time_t datetime::encode(const ymdhns &toencode)
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

/**
 * Gets Current Time.
 *
 * 
 * @return The Current Time
 */
void datetime::now()
{
	value = time(nullptr);	
}

/**
 * Gets current time one day in the past.
 *
 * 
 * @return The current time one day in the past.
 */
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

/**
 * Gets current time on day in the future.
 *
 * 
 * @return The current time on day in the future
 */
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

 	value = encode( newdate);
}

void datetime::midnight()
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	
 	currenttime.hh = 0;
 	currenttime.nn = 0;
 	currenttime.ss = 0;

 	value = encode(currenttime);
}

void datetime::noon()
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	
 	currenttime.hh = 12;
 	currenttime.nn = 0;
 	currenttime.ss = 0;

 	value = encode(currenttime);
}

void datetime::janfirst(int year)
{
	ymdhns currenttime;
 	decode(value, currenttime);

 	currenttime.mm = 1;
 	currenttime.dd = 1;
 	if(year>0) currenttime.yy = year;

 	value = encode(currenttime);
}

std::string datetime::tostring() const
{
	const tm * t = localtime(&value);
	char *tm_str = asctime(t);
	return tm_str;
}

void datetime::fromstring(const std::string datetimestring)
{
    ymdhns currenttime;
    currentime.mm = 0;
    tm whenStart;

    char dstr[16];
    char mstr[16];
	
	// Wed Dec 29 20:28:23 2021
    sscanf(str.c_str(), "%s %s %d %d:%d:%d %d", dstr, mstr, &currenttime.dd, &currenttime.hh, &currenttime.nn, &currenttime.ss, &currenttime.yy);

    for(int idx=0; idx<12;++idx)
    {    	
    	if(strncmp(mstr, MonthsOfYear[idx].c_str(), 3) ==0)
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

    return mktime(&whenStart);
}


void datetime::fromstring(const std::string datetimestring, FfromString func)
{
	if(func != nullptr)
	{
		ymdhns result;
		func(datetimestring,result);
		value = encode(result);
	}
	else
	{
		value = fromstring(datetimestring);
	}
}

/**
 * Sets the the date time
 *
 * @param year 
 * @param month
 * @param day
 * @param hour 
 * @param minute 
 * @param second 
 * @return Returns the current date time.
 */
void datetime::setdatetime(const int year,const int month,const int day, const int hour,const int minute,const int second)
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	currenttime.yy = year;
 	currenttime.mm = month;
 	currenttime.dd = day; 	
 	currenttime.hh = hour;
 	currenttime.nn = minute;
 	currenttime.ss = second;
 	value = encode(currenttime);
}

/**
 * Sets the the date
 *
 * @param year 
 * @param month
 * @param day
 * @return Returns the current date.
 */
void datetime::setdate(const int year,const int month,const int day)
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	currenttime.yy = year;
 	currenttime.mm = month;
 	currenttime.dd = day; 	
 	value = encode(currenttime);
}

/**
 * Sets the the time
 *
 * @param hour 
 * @param minute 
 * @param second 
 * @return Returns the current time.
 */
void datetime::settime(const int hour,const int minute,const int second)
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	currenttime.hh = hour;
 	currenttime.nn = minute;
 	currenttime.ss = second;
 	value = encode(currenttime);
}