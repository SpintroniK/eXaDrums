/*
 * SerialSensorTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "SensorTest.h"

#include <Source/Api/eXaDrumKit.h>

#include "../IO/SpiSensor.h"


using namespace eXaDrumKitApi;
using namespace std::chrono;

namespace Testing
{

	void SensorTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrumKit drumKit(moduleLocation.c_str());

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());

		// Create Sensor
		IO::SpiSensor sensor(0);

		// Add a trigger for drum id 0
		const int snareId = 0;
		drumKit.AddTrigger(snareId);

		// Start drum module
		drumKit.Start();

		int N = 500000;


		for(int i = 0; i < N; i++)
		{

			short value = sensor.Read();

			drumKit.Trig(snareId, value);

		}


		// Stop drum module
		drumKit.Stop();

		return;
	}


}

