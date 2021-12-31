#include "datetime.h"



void datetime::decode(const time_t dt, ymdhns &decoded)
{
	const tm * t = localtime(&dt);
	decoded.yy = t->tm_year + 1900;
	decoded.mm = t->tm_mon + 1;
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


void datetime::now()
{
	value = time(nullptr);	
}


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

int datetime::dayofweek() const
{
    const tm * t = localtime(&value);
    return t->tm_wday;
}

std::string datetime::tostring()  
{    
    std::stringstream ss;
	ymdhns currenttime;
    decode(value, currenttime);
    
    ss << DaysOfWeek[dayofweek()].substr(0,3) << " ";
    ss << MonthsOfYear[currenttime.mm-1].substr(0,3) << " ";
    if(currenttime.dd<10) ss << ' ';
    ss << currenttime.dd << " ";
    if(currenttime.hh<10) ss << '0';
    ss << currenttime.hh;
    ss << ':';
    if(currenttime.nn<10) ss << '0';
    ss << currenttime.nn;
    ss << ':';
    if(currenttime.ss<10) ss << '0';
    ss << currenttime.ss;
    ss << " " << currenttime.yy;

	return ss.str();
}

void datetime::fromstring(const std::string datetimestring)
{
    ymdhns currenttime;
    currenttime.mm = 0;
    tm whenStart;

    char dstr[16];
    char mstr[16];
	
	// Wed Dec 29 20:28:23 2021
    sscanf(datetimestring.c_str(), "%s %s %d %d:%d:%d %d", dstr, mstr, &currenttime.dd, &currenttime.hh, &currenttime.nn, &currenttime.ss, &currenttime.yy);

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

    value = mktime(&whenStart);
}


void datetime::fromstring(const std::string datetimestring, funcfromstring func)
{
	if(func != nullptr)
	{
		ymdhns result;
		func(datetimestring,result);
		value = encode(result);
	}	
}


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


void datetime::setdate(const int year,const int month,const int day)
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	currenttime.yy = year;
 	currenttime.mm = month;
 	currenttime.dd = day; 	
 	value = encode(currenttime);
}

void datetime::settime(const int hour,const int minute,const int second)
{
	ymdhns currenttime;
 	decode(value, currenttime);
 	currenttime.hh = hour;
 	currenttime.nn = minute;
 	currenttime.ss = second;
 	value = encode(currenttime);
}