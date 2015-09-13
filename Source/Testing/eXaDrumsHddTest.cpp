/*
 * eXaDrumsHddTest.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrumsHddTest.h"

#include <Source/Api/eXaDrumKit.h>

#include <iostream>
#include <string>

using namespace eXaDrumKitApi;

namespace Testing
{

	void eXaDrumsHddTest::RunTest()
	{

		std::string moduleLocation("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/Data/");

		eXaDrumKit drumKit(moduleLocation.c_str());

		std::string kitLocation("Kits/default.xml");

		drumKit.LoadKit(kitLocation.c_str());

		std::cout << "Test" << std::endl;

		return;
	}


}


