/*
 * eXaDrumsHddTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrumsHddTest.h"

#include <Source/Api/eXaDrums.h>
#include <Source/IO/HddSensor.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/SensorType.h>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <vector>

using namespace eXaDrumsApi;

namespace Testing
{

	void eXaDrumsHddTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrums drumKit(moduleLocation.c_str(), IO::SensorType::Hdd);

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());



		// Start drum module
		drumKit.Start();


		std::this_thread::sleep_for(std::chrono::seconds(30));

		// Stop drum module
		drumKit.Stop();



		return;
	}


}


