#include "datetime.h"



datetime::now()
{
	value = time(nullptr);	
}