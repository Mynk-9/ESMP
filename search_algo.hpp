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

#ifndef SEARCH_ALGO_ESMP
#define SEARCH_ALGO_ESMP

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

namespace esmp
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
		(FORWARD_ITERATOR _begin, FORWARD_ITERATOR _end, const ITEM_TYPE& item)
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
	  *		      		maximum summing sub-array of variable length in a 1-D
	  *		      		array.
	  * 	@param		A vector, deque, array(STL) etc. which supports the
	  *		      		[] operator and has .size() as method.
	  */
	template <typename T>
	std::pair <int, std::pair <int, int> > kadane (const T& vec)
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

	/**
	  *		@brief		Used to find maximum summing sub-array of variable
	  *					length in an array, vector, deque etc.
	  *		@param		Template Parameters	:	Array type, eg., Vector, Deque etc.
	  *											which support [] operator.
	  *		@param		T vec				:	The vector, deque, etc.
	  *		@param		int length			:	Fixed length of the sub-array.
	  *		@return		std::pair<int, int>	:	First is max sum. Second is
	  *											starting iterator.
	  */
	template <typename T>
	std::pair <int, int> maxSumming_SubArray_fixedLength (const T& vec, const int& length)
	{
		int max_sum = INT_MIN, sum = 0, loc = 0;

		for (int i = 0; i < vec.size(); i++)
		{
			sum += vec[i];
			if (i - length >= 0)
			{
				sum -= vec[i - length];
				if (max_sum < sum)
				{
					max_sum = sum;
					loc = i;
				}
			}
		}

		return {max_sum, loc};
	}
}


#endif
