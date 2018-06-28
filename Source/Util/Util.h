/*
 * Util.h
 *
 *  Created on: 20 Jun 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_UTIL_H_
#define SOURCE_UTIL_UTIL_H_

#include <string>

namespace Util
{

	template <typename T, typename B>
	inline T* GetWidget(B& builder, const std::string& name)
	{
		T* widget = nullptr;
		builder->get_widget(name.data(), widget);

		return widget;
	}


}

#endif /* SOURCE_UTIL_UTIL_H_ */
