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

		std::string GetKitFrameTitle() const { return kitFrameTitle; }
		std::string GetPlayButtonLabel() const { return this->playButtonLabel; }
		std::string GetStopText() const { return "Stop"; }
		std::string GetPlayText() const { return "Play"; }
		std::string GetAddKitButtonLabel() const { return this->addKitButtonLabel; }
		std::string GetdeleteKitButtonLabel() const { return this->deleteKitButtonLabel; }
		std::string GetConfigureButtonLabel() const { return this->configureButtonLabel; }

		void SetPlayButtonText(std::string text);

	private:

		std::string kitFrameTitle;
		std::string playButtonLabel;
		std::string addKitButtonLabel;
		std::string deleteKitButtonLabel;
		std::string configureButtonLabel;

	};

	typedef std::shared_ptr<MainPageModel> MainPageModelPtr;


} /* namespace Gui */

#endif /* SOURCE_MODELS_MAINPAGE_MAINPAGEMODEL_H_ */
