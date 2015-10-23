/*
 * Accelerometer.cpp
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#include "Sensor.h"


namespace IO
{

	Sensor::Sensor(char chan)
	: channel(chan)
	{

		if (!bcm2835_init())
		{
			std::cout << "Could not initialise bcm2835" << std::endl;
			return ;
		}

		// Bcm2835 configuration
		{
			bcm2835_spi_begin();
			bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);		// The default
			bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);						// The default
			bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);		//
			bcm2835_spi_chipSelect(BCM2835_SPI_CS0);						// The default
			bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);		// the default
		}

		return;
	}

	Sensor::~Sensor()
	{

		// End Spi transfer
		bcm2835_spi_end();

		// Close bcm2835 library
		bcm2835_close();

		return;
	}


	short Sensor::Read()
	{

		// Select SPI channel
		char data = 0b11100000 | (channel << 3);

		char mosi[3] = {data};
		char miso[3] = {0};

		// Receive data
		bcm2835_spi_transfernb(mosi, miso, 3);

		// Calculate value from received bits
		short value = ((miso[0] & 0x01) << 11) | (miso[1] << 3) | ((miso[2] >> 5) & 0x07);

		return value;
	}

}


