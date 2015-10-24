/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */

#include "Testing/eXaDrumsHddTest.h"
#include "Testing/SerialSensorTest.h"
#include "Testing/SerialSensorsTest.h"
#include "Testing/GuiHddTest.h"

int main(int argc, char* argv[])
{

	int a = 0;

	Testing::eXaDrumsHddTest::RunTest();
	//Testing::SerialSensorsTest::RunTest();
	//Testing::SerialSensorTest::RunTest();

	//a = Testing::GuiHddTest::RunTest(argc, argv);

	return a;
}
