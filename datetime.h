#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <iostream>
#include <cstring>

const int SecondsPerMinute = 60;
const int SecondsPerHour = 3600;
const int SecondsPerDay = 86400;

const int DaysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::string DaysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const std::string MonthsOfYear[] = { "January", "February", "March", "April", "May", "June", "July",
									"August", "September", "October", "November", "December" };



class datetime
{
	private:
		time_t value = 0;

	public:

};

#endif