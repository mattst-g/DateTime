#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <iostream>
#include <cstring>



 

class datetime
{
	private:
		constexpr int SecondsPerMinute = 60;
		constexpr int SecondsPerHour = 3600;
		constexpr int SecondsPerDay = 86400;

		constexpr int DaysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		constexpr std::string DaysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		constexpr std::string MonthsOfYear[] = { "January", "February", "March", "April", "May", "June", "July",
											"August", "September", "October", "November", "December" };
		time_t value = 0;

		// void decode(int &year, int &month, int &day, int &hour, int &minute, int &second);	
		// void encode(const int year, const int month, const int day, const int hour, const int minute, const int second);

	public:

		datetime() {}

		// datetime(const &other) : value(other.value) {} // copy constructor

		// datetime(const time_t &other_t) : value(other_t) {} // copy constructor

		// virtual ~datetime() {}

		// // copy assign =

		// // move assign =

		// // operator +

		// // operator -

		// // operator ++

		// // operator --

		// void onchangeevent(); // callback lambda

		void now();			
		void yesterday();
		void tomorrow();


		// void midnight();
		// void noon();
		// void janfirst(int year = 0);	

		// std::string tostring() const;
		// void fromstring(const std::string datetimestring);
		// void fromstring(const std::string datetimestring, std::function() ); // with lambda adapter

		// void setdatetime(int year, int month, int day, int hour, int minute, int second);
		// void setdate(int year, int month, int day);
		// void settime(int hour, int minute, int second);

		// int dayofweek() const;
		// std::string dayofweek() const;
		// int dayofyear() const;
		// int weekofyear() const;

		// void addseconds(int count = 1);
		// void addminutes(int count = 1);
		// void addhours(int count = 1);
		// void adddays(int count = 1);

		// void setfirstdayofmonth();
		// void setlastdayofmonth();

		// bool isleapyear() const;

		// bool samedatetime(const datetime &other) const;
		// bool samedate(const datetime &other) const;
		// bool sametime(const datetime &other) const;
		// bool samehour(const datetime &other) const;
		// bool sameminute(const datetime &other) const;
		// bool samesecond(const datetime &other) const;

		// int secondsapart(const datetime &other) const;
		// int minutesapart(const datetime &other) const;
		// int hoursapart(const datetime &other) const;
		// int daysapart(const datetime &other) const;

		// void difference(const datetime &other, int &days, int &hours, int &minutes, int &seconds) const;

		// int year() const;
		// int month() const;
		// std::string month() const;
		// int day() const;
		// int hour() const;
		// int minute() const;
		// int second() const;

		// bool issunday() const;
		// bool ismonday() const;
		// bool istuesday() const;
		// bool iswednesday() const;
		// bool isthursday() const;
		// bool isfriday() const;
		// bool issaturday() const;

};

#endif