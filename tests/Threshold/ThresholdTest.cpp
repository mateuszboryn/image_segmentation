#include <Threshold.h>

#define BOOST_TEST_MAIN

//#include <boost/test/auto_unit_test.hpp>
//#include <boost/test/unit_test_suite.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

//using namespace std;


BOOST_AUTO_TEST_CASE( my_test )
{
	std::cout << "Tutaj: BOOST_AUTO_TEST_CASE( my_test )\n";
}

BOOST_AUTO_TEST_CASE( my_test2 )
{
	std::cout << "Tutaj: BOOST_AUTO_TEST_CASE( my_test2 )\n";
	BOOST_CHECK(false);
}
