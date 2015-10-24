/*
 * Accelerometer.h
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_IO_SENSOR_H_
#define RASPIDRUMS_SOURCE_IO_SENSOR_H_


#include <bcm2835.h>

#include <iostream>


namespace IO
{

	class SpiSensor
	{

	public:
		SpiSensor(char channel);
		virtual ~SpiSensor();

		short Read();


	private:

		char channel;

	};



}

#endif /* RASPIDRUMS_SOURCE_IO_SENSOR_H_ */
