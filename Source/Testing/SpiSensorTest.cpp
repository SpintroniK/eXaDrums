/*
 * SerialSensorTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "SpiSensorTest.h"

#include <Source/Api/eXaDrums.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/SpiSensor.h>
#include <Source/IO/SensorType.h>


using namespace eXaDrumsApi;
using namespace std::chrono;

namespace Testing
{

	void SpiSensorTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrums drumKit(moduleLocation.c_str(), IO::SensorType::Spi);

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

