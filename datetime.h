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

		datetime() {}

		datetime(const &other) : value(other.value) {} // copy constructor

		virtual ~datetime() {}

		// copy assign =

		// move assign =

		// operator +

		// operator -

		// operator ++

		// operator --

		void now();		

		std::string tostring();
		void fromstring();

		void setdatetime(int &year, int &month, int &day, int &hour, int &minute, int &second);
		void setdate(int &year, int &month, int &day);
		void settime(int &hour, int &minute, int &second);

		int dayofweek();
		int dayofyear();
		int weekofyear();

		void addseconds(int count = 1);
		void addminutes(int count = 1);
		void addhours(int count = 1);
		void adddays(int count = 1);

		void setfirstdayofmonth();
		void setlastdayofmonth();

		bool isleapyear();

		bool samedatetime(const datetime &other);
		bool samedate(const datetime &other);
		bool sametime(const datetime &other);
		bool samehour(const datetime &other);
		bool sameminute(const datetime &other);
		bool samesecond(const datetime &other);

		int secondsapart(const datetime &other);
		int minutesapart(const datetime &other);
		int hoursapart(const datetime &other);
		int daysapart(const datetime &other);

		void difference(const datetime &other, int &days, int &hours, int &minutes, int &seconds);
};

#endif