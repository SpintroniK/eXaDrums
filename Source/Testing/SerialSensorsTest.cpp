/*
 * SerialSensorsTest.cpp
 *
 *  Created on: 29 Sep 2015
 *      Author: jeremy
 */

#include "SerialSensorsTest.h"

#include <Source/Api/eXaDrumKit.h>
#include <Source/IO/Serial.h>


using namespace eXaDrumKitApi;
using namespace std::chrono;

namespace Testing
{

	void SerialSensorsTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrumKit drumKit(moduleLocation.c_str());

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());

		// Create Serial sensor
		std::unique_ptr<IO::ISensor> sensor(new IO::Serial);

		// Add a trigger for drum id 0
		const int snareId = 0;
		drumKit.AddTrigger(snareId);

		const int tomtomId = 1;
		drumKit.AddTrigger(tomtomId);

		// Start drum module
		drumKit.Start();

		int N = 500000;


		for(int i = 0; i < N; i++)
		{

			short value = 16.0f * short((unsigned char)sensor->GetData(0));

			drumKit.Trig(snareId, value);

			//value = 16.0f * short((unsigned char)serialSensor.Read('0'));

			//drumKit.Trig(tomtomId, value);

		}


		// Stop drum module
		drumKit.Stop();

		return;
	}


}


