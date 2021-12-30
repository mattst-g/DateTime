#include "datetime.h"



void datetime::decode(const time_t dt, ymdhns & decoded)
{
	const tm * t = localtime(&dt);
	decoded.yy = t->tm_year;
	decoded.mm = t->tm_mon;
	decoded.dd = t->tm_mday;
	decoded.hh = t->tm_hour;
	decoded.nn = t->tm_min;
	decoded.ss = t->tm_sec;
}

time_t datetime::encode(const int year, const ymdhns & toencode)
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

 	newdate.hh=currenttime.hh;
 	newdate.nn=currenttime.nn;
 	newdate.ss=currenttime.ss;

 	encode(value, newdate);
}

void datetime::tomorrow()
{	
	ymdhns currenttime;
 	decode(value, currenttime);

 	time_t temp = time(nullptr);
 	temp += SecondsPerDay;

 	ymdhns newdate;
 	decode(temp, newdate);

 	newdate.hh=currenttime.hh;
 	newdate.nn=currenttime.nn;
 	newdate.ss=currenttime.ss;

 	encode(value, newdate);
}