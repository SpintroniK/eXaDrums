/*
 * SerialSensorsTest.cpp
 *
 *  Created on: 29 Sep 2015
 *      Author: jeremy
 */

#include "SerialSensorsTest.h"

#include <Source/Api/eXaDrumKit.h>
#include <Source/IO/Serial.h>
#include <Source/IO/SensorType.h>


using namespace eXaDrumKitApi;
using namespace std::chrono;

namespace Testing
{

	void SerialSensorsTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrumKit drumKit(moduleLocation.c_str(), IO::SensorType::UsbSerial);

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());



		// Stop drum module
		drumKit.Stop();

		return;
	}


}


