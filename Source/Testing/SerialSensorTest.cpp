/*
 * SerialSensorTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "SerialSensorTest.h"

#include <Source/Api/eXaDrums.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/Serial.h>
#include <Source/IO/SensorType.h>

#include <memory>

using namespace eXaDrumsApi;
using namespace std::chrono;

namespace Testing
{

	void SerialSensorTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrums drumKit(moduleLocation.c_str(), IO::SensorType::UsbSerial);

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());

		// Create Serial sensor

		//sensor->Open();




		// Stop drum module
		drumKit.Stop();

		//serialSensor.Close();

		return;
	}


}

