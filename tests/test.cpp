#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../srcs/Application.cpp"
#include <string>
#include <iostream>
#include <streambuf>
#include <stdlib.h>
#include <string>
#include <sstream>

TEST_CASE( "App run", "[test run]" ) {
	Application app;
	app.runApp();
}
