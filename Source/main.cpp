/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */

#include "Testing/eXaDrumsHddTest.h"
#include "Testing/SerialSensorTest.h"
#include "Testing/SerialSensorsTest.h"

int main(int argc, char* argv[])
{

	//Testing::eXaDrumsHddTest::RunTest();
	//Testing::SerialSensorsTest::RunTest();

	Testing::SerialSensorTest::RunTest();

	return 0;
}
