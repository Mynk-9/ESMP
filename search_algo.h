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

#ifndef SEARCH_ALGO_9THSKY
#define SEARCH_ALGO_9THSKY

/**
*	@brief	this section includes searching algorithms
*		   and shall be reusing existing algorithms in STL
*		   for better functionality and preventing reinventing
*		   the same thing.
*/

#include <iterator>
#include <vector>
#include <deque>
#include <algorithm>

namespace ninth_sky
{

	/**
	*   @brief  This algorithmic function is an extension to the Binary Search in STL.
	*   @param  Template Parameters			 :   Type of Array, e.g., vector &lt;int&gt;.
	*   @param  Template Parameters			 :   Item type in Array, e.g., int.
	*   @param  ARRAY_TYPE::iterator _begin	 :   The beginning random access or forward iterator.
	*   @param  ARRAY_TYPE::iterator _end	   :   The ending random access or forward iterator.
	*/
	template <typename ARRAY_TYPE, typename ITEM_TYPE>
	std::pair <int, int> binary_search
		(const typename ARRAY_TYPE::iterator _begin, const typename ARRAY_TYPE::iterator _end, ITEM_TYPE item)
	{
		typename ARRAY_TYPE::iterator first, last;
		first = _begin < _end ? _begin : _end;
		last = _begin == first ? _end : _begin;

		typename ARRAY_TYPE::iterator i, j;
		bool right_searched = false;

		i = j = std::lower_bound(first, last, item);
		if (i == last || *i != item)
			return {-1, -1};
		if (i == (last - 1))
			right_searched = true;

		while (!right_searched)
		{
			if (*(++j) != item)
			{
				j--;
				right_searched = true;
			}
		}

		std::pair <int, int> index_range;

		index_range = {(i - first), (j - first)};

		return index_range;
	}

}


#endif
