/*
 * Subject.cpp
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#include "Subject.h"

namespace Gui
{

	void Subject::Subscribe(Observer* observer)
	{

		observers.insert(observer);

		return;
	}

	void Subject::Unsubscribe(Observer* observer)
	{

		observers.erase(observer);

		return;
	}

	// PROTECTED

	void Subject::Notify()
	{

		std::for_each(observers.begin(), observers.end(), [](Observer* observer)
		{
			observer->Update();
		});

		return;
	}


} /* namespace Gui */

