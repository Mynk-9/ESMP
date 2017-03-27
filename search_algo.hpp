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
#include "error_submission.hpp"
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
	*   @param  Template Parameters			 :   Forward/Random Access Iterator
	*											 of the vector, deque, array(STL) etc.
	*   @param  Template Parameters			 :   Item type in Array, e.g., int.
	*   @param  FORWARD_ITERATOR _begin	 	 :   The beginning random access or forward iterator.
	*   @param  FORWARD_ITERATOR _end	   	 :   The ending random access or forward iterator.
	*/
	template <typename FORWARD_ITERATOR, typename ITEM_TYPE>
	std::pair <int, int> binarySearch
		(FORWARD_ITERATOR _begin, FORWARD_ITERATOR _end, ITEM_TYPE item)
	{
		if (_begin > _end)
			std::swap(_begin, _end);

		FORWARD_ITERATOR i, j;
		bool right_searched = false;

		i = j = std::lower_bound(_begin, _end, item);
		if (i == _end || *i != item)
			return {-1, -1};
		if (i == (_end - 1))
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

		index_range = {(i - _begin), (j - _begin)};

		return index_range;
	}

	/**
	  * 	@brief		Uses Kadane's Algorithm to find
	  *					maximum summing sub-array in a 1-D
	  *					array.
	  *		@param		A vector, deque, array(STL) etc. which supports the
	  *					[] operator and has .size() as method.
	  */
	template <typename T>
	std::pair <int, std::pair <int, int> > kadane (T vec)
	{
		std::pair <int, std::pair <int, int> > p;
		int max_here = 0, max_so_far = INT_MIN;
		int i = 0, j = 0;
		bool swtch = false;

		for (int k = 0; k < vec.size(); k++)
		{
			max_here += vec[k];
			if (max_so_far < max_here)
			{
				max_so_far = max_here;
				j = k;
			}
			if (max_here < 0)
			{
				max_here = 0;
				i = k + 1;
			}
		}

		p = {max_so_far, {i, j}};
		return p;
	}
}


#endif
