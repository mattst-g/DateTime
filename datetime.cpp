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
void datetime::setdatetime(int year, int month, int day, int hour, int minute, int second)
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
void datetime::setdate(int year, int month, int day)
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
void datetime::settime(int hour, int minute, int second)
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	currenttime.hh = hour;
 	currenttime.nn = minute;
 	currenttime.ss = second;
 	value = encode(currenttime);
}