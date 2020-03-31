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

#ifndef ERROR_SUBMISSION_ESMP
#include "error_submission.hpp"
#endif

#ifndef ALGORITHMS_ESMP
#define ALGORITHMS_ESMP

#include <type_traits>

/**
*	@brief		include searching algorithms
*/
#include "search_algo.hpp"

namespace esmp
{
	/**
	 * 	@brief	Raises a to the power of b
	 * 	@param	Template Parameters	:	Numeric datatype like int, short, char, long etc.
	 * 	@param	T a					:	The number to which power is to be raised.
	 * 	@param	T b					:	The value of power to be raised.
	 * 	@return	T pow				:	pow is a raised to the power of b.
	 */
	template <typename T>
	T power(T a, T b)
	{
		/// check for possible template errors
		static_assert(std::is_integral<T>::value, "esmp::power function requires integral value.");

		T pow = 1;
		while (b--)		/// loop runs b times
			pow *= a;
		
		return pow;
	}

	/**
	 * 	@brief	Returns the next number which is a power of 2.
	 * */
	template <typename T>
	T nextPowerOf2 (T n)
	{
		/// check for possible template errors
		static_assert(std::is_integral<T>::value, "esmp::nextPowerOf2 function requires integral value.");

		--n;
		n |= n >> 1;
		n |= n >> 2;
		n |= n >> 4;
		n |= n >> 8;
		n |= n >> 16;
		++n;
		return n;
	}
}

#endif