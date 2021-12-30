#include "datetime.h"



void datetime::now()
{
	value = time(nullptr);	
}


void datetime::yesterday()
{
	time_t temp = time(nullptre);
	value = temp - SecondsPerDay;
}

void datetime::tomorrow()
{	
	time_t temp = time(nullptre);
	value = temp + SecondsPerDay;
}