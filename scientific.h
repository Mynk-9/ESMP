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

#ifndef SCIENTIFIC_9THSKY
#define SCIENTIFIC_9THSKY

#include <list>
#include <iterator>
#include <utility>
#include <string>

namespace ninth_sky
{
	/**
	*	@brief      This class include a scientific data type with extremely large
	*               possible value calculations.
	*/
	class integer_xl
	{
		private:
			std::list <short int> value;
			bool negative = false;

		public:
			void appendLeft (short int a, int counter = 1)
			{
				while (counter--)
				    this -> value.push_front(a);
			}
			void appendRight (short int a, int counter = 1)
			{
			    while (counter--)
			        this -> value.push_back(a);
			}
			int length ()
			{
				return this -> value.size();
			}
			void setNegative (bool yesno = true)
			{
				this -> negative = yesno;
			}
			bool isNegative ()
			{
			    return this -> negative;
			}
			void assign (std::list <short int> lst)
			{
				auto start =		lst.begin(),
					 terminate =	lst.end();

				this -> value.clear();
				bool swtch = false;
				for (; start != terminate; start++)
				{
					if (*start != 0)
						swtch = true;
					if (swtch)
						this -> value.push_back(((short int)(*start)) % 10);
				}
			}
			void refresh ()
			{
			    if (this -> value.empty())
				{
					this -> setNegative(false);
					return;
				}
			    auto i = this -> value.begin(),
			         l = this -> value.end();

                for (; i != l; i++)
                {
                    if (*i == 0)
                        this -> value.pop_front();
                    else
                        break;
                }
			}
			void clear ()
			{
			    this -> value.clear();
			    this -> setNegative(false);
			}
			std::string getString ()
			{
			    std::string str;
			    auto i = this -> value.begin(),
			         j = this -> value.end();
                for (; i != j; i++)
                    str += std::to_string (*i);
                return str;
			}

			/**
			*   @brief  Assignment Operators
			*/
			void operator = (const std::string number)
			{
			    short int magic_number = 48;	  /// used to convert char to int

				this -> value.clear();
				bool swtch = false;
				for (char c : number)
				{
					short int si = (int)(c - magic_number);
					if (si < 10 && si >= 0 && swtch)
						this -> value.push_back (si);
					else if (!swtch && si > 0 && si < 10)
					{
						this -> value.push_back (si);
						swtch = true;
					}
				}
				if (number.substr(0, 1) == "-")
					this -> setNegative(true);
			}
			void operator = (const integer_xl& ixl)
			{
				this -> value = ixl.value;
				this -> negative = ixl.negative;
			}

			/**
			*   @brief  Relational Operators
			*/
			bool operator == (const integer_xl& ixl)
			{
				if (this -> negative != ixl.negative)
					return false;
				else if (this -> value.size() != ixl.value.size())
					return false;
				else
				{
					auto i = this -> value.begin();
					auto j = ixl.value.begin();
					auto l1 = this -> value.end();
					while (i != l1)
					{
						if (*i != *j)
							return false;
						i++;
						j++;
					}
				}
				return true;
			}
			bool operator > (const integer_xl& ixl)
			{
				bool answer, invert;

				if (this -> negative != ixl.negative)
				{
					if (this -> negative)
						return false;
					else
						return true;
				}
				else if (this -> negative == ixl.negative)
				{
					if (this -> value == ixl.value)
						return false;
					else if (this -> negative && ixl.negative)
						invert = true;
					else
						invert = false;
				}

				if (this -> value.size() > ixl.value.size())
					answer = true;
				else if (this -> value.size() <  ixl.value.size())
					answer = false;
				else
				{
					auto i = this -> value.begin();
					auto j = ixl.value.begin();
					auto l1 = this -> value.end();
					while (i != l1)
					{
						if (*i > *j)
						{
							answer = true;
							break;
						}
						else if (*i < *j)
						{
							answer =  false;
							break;
						}
						i++;
						j++;
					}
				}
				if (invert)
					answer = !answer;
				return answer;
			}
			bool operator < (const integer_xl& ixl)
			{
				bool answer, invert;

				if (this -> negative != ixl.negative)
				{
					if (this -> negative)
						return true;
					else
						return false;
				}
				else if (this -> negative == ixl.negative)
				{
					if (this -> value == ixl.value)
						return false;
					else if (this -> negative && ixl.negative)
						invert = true;
					else
						invert = false;
				}

				if (this -> value.size() > ixl.value.size())
					answer =  false;
				else if (this -> value.size() < ixl.value.size())
					answer = true;
				else
				{
					auto i = this -> value.begin();
					auto j = ixl.value.begin();
					auto l1 = this -> value.end();
					while (i != l1)
					{
						if (*i < *j)
						{
							answer = true;
							break;
						}
						else if (*i > *j)
						{
							answer = false;
							break;
						}
						i++;
						j++;
					}
				}
				if (invert)
					answer = !answer;
				return answer;
			}
			bool operator >= (const integer_xl& ixl)
			{
				integer_xl _ixl;
				_ixl.assign(this -> value);
				_ixl.setNegative(this -> negative);
				if (_ixl == ixl)
					return true;
				else if (_ixl > ixl)
					return true;
				else
					return false;
			}
			bool operator <= (const integer_xl& ixl)
			{
				integer_xl _ixl;
				_ixl.assign(this -> value);
				_ixl.setNegative(this -> negative);
				if (_ixl == ixl)
					return true;
				else if (_ixl < ixl)
					return true;
				else
					return false;
			}

			/**
			*   @brief  Arithmetic Operators
			*/
			integer_xl operator - (integer_xl ixl)
			{
			    integer_xl answer, ths;
			    ths.assign(this -> value);
			    ths.setNegative(this -> isNegative());

			    /**
			    *   We're going to substract ixl from ths, i.e, ths - ixl
			    */

			    /**
			    *   @possibleCases  :   BOTH EQUAL
                *                       +ve - +ve
                *                       +ve - -ve
                *                       -ve - +ve
                *                       -ve - -ve
			    */

			    if (ths.isNegative() == false)
                {
                    if (ixl.isNegative() == false)
                    {
                        ninth_sky::error_report.debug_write("case 1");
                        /// x - y = x-y

                        std::_List_iterator <short int> i, j, l1, l2;
                        if (ths == ixl)
                        {
                            answer = "0";
                            answer.refresh();
                            return answer;
                        }
                        else if (ths > ixl)
                        {
                            i = ths.value.end();
                            l1 = ths.value.begin();
                            j = ixl.value.end();
                            l2 = ixl.value.begin();
                        }
                        else
                        {
                            i = ixl.value.end();
                            l1 = ixl.value.begin();
                            j = ths.value.end();
                            l2 = ths.value.begin();
                            answer.setNegative();
                        }

                        /// /////////////////////////// ///
                        /// /////////////////////////// ///
                        ///   Now we're supposed to     ///
                        ///   substract (j, l2] from    ///
                        ///   (i, l1].                  ///
                        /// /////////////////////////// ///
                        /// /////////////////////////// ///

                        bool swtch_i = true,
                             swtch_j = true,
                             carry   = 0;
                        short int tmp = 0;

                        while (swtch_i || swtch_j)
                        {
                            if (swtch_i && i-- == l1)
                                swtch_i = false;
                            else if (swtch_i)
                                tmp = *i;

                            if (swtch_j && j-- == l2)
                                swtch_j = false;
                            else if (swtch_j)
                                tmp -= *j;

                            tmp -= carry;

                            if (tmp < 0)
                            {
                                carry = 1;
                                tmp += 10;
                            }
                            else
                                carry = 0;

                            answer.appendLeft(tmp);
                            tmp = 0;
                        }

                    }
                    else
                    {
                        ninth_sky::error_report.debug_write("case 2");
                        /// x - -y = x+y

                        ixl.setNegative (false);
                        answer = ths + ixl;
                    }
                }
                else
                {
                    if (ixl.isNegative() == false)
                    {
                        ninth_sky::error_report.debug_write("case 3");
                        /// -x - y = -(x+y)

                        ths.setNegative (false);
                        answer = ths + ixl;
                        answer.setNegative (true);
                    }
                    else
                    {
                        ninth_sky::error_report.debug_write("case 4");
                        /// -x - -y = -x+y = y-x

                        ths.setNegative (false);
                        ixl.setNegative (false);
                        answer = ixl - ths;
                    }
                }

                answer.refresh();
                return answer;
			}
			integer_xl operator + (integer_xl ixl)
			{
				integer_xl answer;

				if (this -> negative != ixl.negative)
				{
					integer_xl ths;
					ths.assign(this -> value);
					if (this -> negative)
                    {
                        answer = (ixl - ths);
                    }
					else
					{
					    ixl.setNegative(false);
						answer = (ths - ixl);
					}
					return answer;
				}

				answer.setNegative(this -> negative);

				bool carry =	0,
					 swtch_i =  true,
					 swtch_j =  true;
				int tmp = 0;
				auto i =	this -> value.end();
				auto j =	ixl.value.end();
				auto l1 =   this -> value.begin();
				auto l2 =   ixl.value.begin();

				while (swtch_i || swtch_j)
				{
					if (swtch_i && i-- == l1)
						swtch_i = false;
					else if (swtch_i)
						tmp = *i;
					if (swtch_j && j-- == l2)
						swtch_j = false;
					else if (swtch_j)
						tmp += *j;
					tmp += carry;

					if (tmp >= 10)
					{
						tmp -= 10;
						carry = 1;
					}
					else
						carry = 0;

					ninth_sky::error_report.debug_write(tmp); /// debug
					answer.appendLeft(tmp);
					tmp = 0;
				}

				answer.refresh();
				if (carry == 1)
					answer.appendLeft(carry);

				return answer;
			}
			void operator += (const integer_xl& ixl)
			{
			    integer_xl ths, answer;
			    ths.assign(this -> value);
			    ths.setNegative(this -> negative);
			    answer = ths + ixl;
			    this -> value = answer.value;
			    this -> negative = answer.isNegative();
			}
			void operator -= (const integer_xl& ixl)
			{
			    integer_xl ths, answer;
			    ths.assign(this -> value);
			    ths.setNegative(this -> negative);
			    answer = ths - ixl;
			    this -> value = answer.value;
			    this -> negative = answer.isNegative();
			}
			integer_xl operator * (const integer_xl& ixl)
			{
			    integer_xl answer, _ixl;

                bool swtch_i = true,
                     swtch_j = true;
                short int tmp = 1, carry = 0;
                long int counter = 0;
                auto i = this -> value.end(),
                    l1 = this -> value.begin();
                auto j = ixl.value.end(),
                    l2 = ixl.value.begin();

                while (i-- != l1)
                {
                    while (j-- != l2)
                    {
                        tmp = (*i)*(*j);
                        tmp += carry;
                        if (tmp >= 10)
                        {
                            carry = tmp/10;
                            tmp %= 10;
                        }
                        else
                            carry = 0;
                        _ixl.appendLeft(tmp);
                    }
                    _ixl.appendRight(0, counter++);
                    answer += _ixl;
                    _ixl.clear();
                    j = ixl.value.end();
                }

                if (this -> negative != ixl.negative)
                    answer.setNegative();
                answer.refresh();
                return answer;
			}

			/**
			*   @brief  IO operators
			*/
			friend std::ostream& operator << (std::ostream& out, const integer_xl& ixl)
			{
				if (ixl.value.size() == 0)
					out << 0;
				if (ixl.negative == true && ixl.value.size() != 0)
					out << "-";
				for (auto i = ixl.value.begin(); i != ixl.value.end(); i++)
					out << (*i);
				out.flush();
			}
			friend std::istream& operator >> (std::istream& in, integer_xl& ixl)
			{
				std::string str;
				in >> str;
				ixl = str;
			}
	};
}


#endif
