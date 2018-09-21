#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../srcs/Skat.cpp"
#include <string>
#include <iostream>
#include <streambuf>
#include <stdlib.h>
#include <string>
#include <sstream>

// class CoutRedirect {
// public:
//     CoutRedirect() {
//         old = std::cout.rdbuf( buffer.rdbuf() ); // redirect cout to buffer stream
//     }

//     std::string getString() {
//         return buffer.str(); // get string
//     }

//     ~CoutRedirect( ) {
//         std::cout.rdbuf( old ); // reverse redirect
//     }

// private:
//     std::stringstream buffer;
//     std::streambuf * old;
// };


// TEST_CASE( "Skat use", "[cout]" ) {
// 	Skat s("Leo", 5);
// 	CoutRedirect c;
// 	std::string text = c.getString();

// 	s.useStimPaks();
// 	CHECK(text == "Time to kick some ass and chew bublle gum.\n\n");
// }

TEST_CASE( "Skat getters", "[factorial]" ) {
	Skat s("Bob", 3);

	REQUIRE(s.stimPaks() == 3);
	REQUIRE(s.stimPaks(1) == 1);
	REQUIRE(s.stimPaks(5) == 5);
	REQUIRE(s.name() == "Bob");
}
