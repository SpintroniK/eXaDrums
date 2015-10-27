/*
 * SerialSensorTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "SerialSensorTest.h"

#include <Source/Api/eXaDrumKit.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/Serial.h>

#include <memory>

using namespace eXaDrumKitApi;
using namespace std::chrono;

namespace Testing
{

	void SerialSensorTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrumKit drumKit(moduleLocation.c_str());

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());

		// Create Serial sensor
		std::unique_ptr<IO::ISensor> sensor(new IO::Serial);

		//sensor->Open();

		// Add a trigger for drum id 0
		const int snareId = 0;
		drumKit.AddDrum(snareId);

		// Start drum module
		drumKit.Start();

		int N = 500000;


		for(int i = 0; i < N; i++)
		{

			short value = 16.0f * short((unsigned char)sensor->GetData(0));

			drumKit.Trig(snareId, value);

		}


		// Stop drum module
		drumKit.Stop();

		//serialSensor.Close();

		return;
	}


}

