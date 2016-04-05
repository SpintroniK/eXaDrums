/*
 * Model.h
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_MODELS_MODEL_H_
#define SOURCE_MODELS_MODEL_H_

#include "../Observers/Subject.h"

#include <memory>

namespace Gui
{

	class Model : public Subject
	{

	public:

		virtual ~Model(){};


	};

	typedef std::shared_ptr<Model> ModelPtr;

}

#endif /* SOURCE_MODELS_MODEL_H_ */
