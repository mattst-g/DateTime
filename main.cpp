#include <iostream>
#include "datetime.h"


int main(int argc, char*argv[])
{
	datetime t;

	std::cout << t.tostring() << "\n";

	t.now();
	std::cout << t.tostring() << "\n";

	t.settime(2,30,40);
	std::cout << t.tostring() << "\n";

	t.yesterday();
	std::cout << t.tostring() << "\n";
	
	t.tomorrow();
	std::cout << t.tostring() << "\n";


	return 0;
}