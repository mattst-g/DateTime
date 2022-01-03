#define CATCH_CONFIG_MAIN 


#include <iostream>
#include "catch2.h"


#include "datetime.h"

const std::string source01 = "Wed Dec 29 20:28:23 2021";
 

TEST_CASE("Define a time and test with string comparison", "[basic creation]") 
{	
	datetime test(source01);
	std::string result = test.tostring();	
	REQUIRE( result == source01 );
}

TEST_CASE("Add seconds", "[basic creation]") 
{	
	datetime test(source01);	
	
	SECTION("Time and Date Adjustments")
	{
		test.addseconds(37);
		std::string result = test.tostring();	
		REQUIRE( result == "Wed Dec 29 20:29:00 2021" );		
		//
		test.addminutes(31);
		result = test.tostring();	
		REQUIRE( result == "Wed Dec 29 21:00:00 2021" );		
		//
		test.addhours(3);			
		result = test.tostring();	
		REQUIRE( result == "Thu Dec 30 00:00:00 2021" );				
		//
		test.adddays(-5);			
		result = test.tostring();	
		REQUIRE( result == "Sat Dec 25 00:00:00 2021" );				
		//
		test.addminutes(-30);			
		result = test.tostring();	
		REQUIRE( result == "Fri Dec 24 23:30:00 2021" );		
		//
		test.addhours(-10);			
		result = test.tostring();	
		REQUIRE( result == "Fri Dec 24 13:30:00 2021" );				
		//
		test.addseconds(-8);			
		result = test.tostring();	
		REQUIRE( result == "Fri Dec 24 13:29:52 2021" );				
	}
}



TEST_CASE("Same", "[comparison]") 
{
	datetime test(source01);	
	datetime other(source01);	

	REQUIRE(test.samedatetime(other));

	other.addseconds();
	REQUIRE(!test.samedatetime(other));
	REQUIRE(test.samedate(other));
	REQUIRE(test.samehour(other));
	REQUIRE(test.sameminute(other));
	REQUIRE(!test.samesecond(other));
	other.addseconds(-1);

	other.addminutes();
	REQUIRE(!test.samedatetime(other));
	REQUIRE(test.samedate(other));
	REQUIRE(test.samehour(other));
	REQUIRE(!test.sameminute(other));
	REQUIRE(test.samesecond(other));
	other.addminutes(-1);
	
	other.addhours();
	REQUIRE(!test.samedatetime(other));
	REQUIRE(test.samedate(other));
	REQUIRE(!test.samehour(other));
	REQUIRE(test.sameminute(other));
	REQUIRE(test.samesecond(other));
	other.addhours(-1);

	other.adddays();
	REQUIRE(!test.samedatetime(other));
	REQUIRE(test.sametime(other));
	REQUIRE(test.samehour(other));
	REQUIRE(test.sameminute(other));
	REQUIRE(test.samesecond(other));
	other.adddays(-1);


	REQUIRE(test.samedatetime(other));
}




TEST_CASE("Appart", "[comparison]") 
{
	datetime test(source01);	
	datetime other(source01);	

	REQUIRE( test.secondsapart(other) == 0);
	other.addseconds(1234);
	REQUIRE( test.secondsapart(other) == 1234);
	other.addseconds(-2468);
	REQUIRE( test.secondsapart(other) == -1234);

	REQUIRE( test.daysapart(other) == 0);
	other.addseconds(1234);

	other.addminutes(90);
	REQUIRE( test.minutesapart(other) == 90);
	other.addseconds( 60 * 60 * 24 * 5);
	REQUIRE( test.daysapart(other) == 5);
}

TEST_CASE("Operators" ,"[comparison]")
{
	datetime test(source01);	
	datetime other;
	datetime diffother;
	other = test;
	diffother = test;


	REQUIRE( test.samedatetime(other) );

	REQUIRE( test == other );

	diffother.addseconds(100);

	REQUIRE( !test.samedatetime(diffother) );

	REQUIRE( test != diffother );

	REQUIRE( test < diffother );
	REQUIRE( test <= diffother );
	REQUIRE( test <= other );

	REQUIRE( diffother > test );
	REQUIRE( diffother >= test );
	REQUIRE( other >= test );

	datetime shift1(60); // 60 seconds 
	datetime shift2(-30); // -30 seconds 

	other = test;

	test.addseconds(60);

	REQUIRE( test != other);

	other += shift1;
	REQUIRE( test == other);

	other = test;	
	test.addseconds(-30);
	other += shift2;
	REQUIRE( test == other);


}