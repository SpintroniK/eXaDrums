/*
 * SerialSensorTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "SpiSensorTest.h"
#include <Source/Api/eXaDrumKit.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/SpiSensor.h>
#include <Source/IO/SensorType.h>


using namespace eXaDrumKitApi;
using namespace std::chrono;

namespace Testing
{

	void SensorTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrumKit drumKit(moduleLocation.c_str(), IO::SensorType::Spi);

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());


		// Stop drum module
		drumKit.Stop();

		return;
	}


}

