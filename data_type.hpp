/**

Copyright 2017 Mayank Mathur

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef ERROR_SUBMISSION_9THSKY
#include "error_submission.h"
#endif

#ifndef DATA_TYPE_9THSKY
#define DATA_TYPE_9THSKY

#include <string>
#include <typeinfo>

#ifdef __GNUG__
	#include <cxxabi.h>
#endif // __GNUG__

namespace ninth_sky
{
	struct data_type
	{
		/**
		*	@brief	Gets the name of data type.
		*	@param	The data object.
		*/
		std::string getName (auto& instance)
		{

#ifdef __GNUG__
			int temp;
			return abi::__cxa_demangle(typeid(instance).name(), 0, 0, &temp);
#else
			return typeid(instance).name();
#endif // __GNUG__
		}
	} data_type;
}


#endif