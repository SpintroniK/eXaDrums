/*
 * eXaDrumsHddTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrumsHddTest.h"

#include <Source/Api/eXaDrumKit.h>
#include <Source/IO/Sensor.h>
#include <Source/IO/HddSensor.h>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>

using namespace eXaDrumKitApi;

namespace Testing
{

	void eXaDrumsHddTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");
		eXaDrumKit drumKit(moduleLocation.c_str());

		std::string kitLocation("Kits/default.xml");
		drumKit.LoadKit(kitLocation.c_str());

		// Create Hdd sensor
		std::string sensorFile(moduleLocation + "../out.raw");
		std::unique_ptr<IO::Sensor> sensor(new IO::HddSensor(sensorFile.c_str()));

		// Add a trigger for drum id 0
		const int snareId = 0;
		drumKit.AddTrigger(snareId);

		// Start drum module
		drumKit.Start();

		//int N = hddSensor.GetDataLength();

		int N = 1000000;

		for(int i = 0; i < N; i++)
		{

			short value = sensor->GetData(0);
			drumKit.Trig(snareId, value);

		}

		// Stop drum module
		drumKit.Stop();

		return;
	}


}


