/*
 * MainPageModel.h
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_MODELS_MAINPAGE_MAINPAGEMODEL_H_
#define SOURCE_MODELS_MAINPAGE_MAINPAGEMODEL_H_

#include "../Model.h"

#include <string>
#include <memory>

namespace Gui
{

	class MainPageModel : public Model
	{

	public:

		MainPageModel();
		virtual ~MainPageModel();

		std::string GetPlayButtonText() const { return this->playButtonText; }
		std::string GetStopText() const { return "Stop"; }
		std::string GetPlayText() const { return "Play"; }
		std::string GetKitFrameTitle() const { return kitFrameTitle; }

		void SetPlayButtonText(std::string text);

	private:

		std::string playButtonText;
		std::string kitFrameTitle;

	};

	typedef std::shared_ptr<MainPageModel> MainPageModelPtr;


} /* namespace Gui */

#endif /* SOURCE_MODELS_MAINPAGE_MAINPAGEMODEL_H_ */
