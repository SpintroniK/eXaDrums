/*
 * Observer.h
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_OBSERVERS_OBSERVER_H_
#define SOURCE_OBSERVERS_OBSERVER_H_


namespace Gui
{

	class Observer
	{

	public:

		virtual ~Observer(){};

		virtual void Update() = 0;

	private:



	};


}


#endif /* SOURCE_OBSERVERS_OBSERVER_H_ */
