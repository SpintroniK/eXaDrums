/*
 * Subject.h
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_OBSERVERS_SUBJECT_H_
#define SOURCE_OBSERVERS_SUBJECT_H_

#include "Observer.h"

#include <algorithm>
#include <set>

namespace Gui
{

	class Subject
	{

	public:

		virtual ~Subject(){};

		void Subscribe(Observer* observer);
		void Unsubscribe(Observer* observer);

	protected:

		void Notify();

	private:

		std::set<Observer*> observers;

	};

} /* namespace Gui */


#endif /* SOURCE_OBSERVERS_SUBJECT_H_ */
