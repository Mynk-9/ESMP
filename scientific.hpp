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

#ifndef SCIENTIFIC_9THSKY
#define SCIENTIFIC_9THSKY

#include <list>
#include <iterator>
#include <utility>
#include <string>

/// ################################################
/// ######### > Adding Decimal Support < ###########
/// ######### > Adding Division Support < ##########
/// @@@@@ > Support added for extra functions < @@@@
/// @@ > Support pending for operator overloads < @@
/// ################################################
///
/// ++++++++++++++++++++++++++++++++++++++++++++++++
///
/// ################################################
/// ####### > Irrational Support Pending < #########
/// ################################################

namespace ninth_sky
{
	/**
	  *	@brief	  This class include a scientific data type with extremely large
	  *			   possible value calculations but only integer type.
	  */
	class integer_xl: public object
	{
		protected:
			std::list <short int> value;
			std::list <short int> decimal_value;
			bool negative = false;
			bool hasDecimal = false;

		public:
			/**
			  *		@brief	Append a digit on the left to the value.
			  *		@param	short int a	:	The digit
			  *		@param	int repeater:	Optional. Number of times to repeat.
			  */
			void appendLeft (short int a, int repeater = 1)
			{
				while (repeater--)
					this -> value.push_front(a);
			}
			/**
			  *		@brief	Append a digit on the right to the value.
			  *		@param	short int a	:	The digit
			  *		@param	int repeater:	Optional. Number of times to repeat.
			  */
			void appendRight (short int a, int repeater = 1)
			{
				if (hasDecimal)
				{
					while (repeater--)
						this -> decimal_value.push_back(a);
				}
				else
					while (repeater--)
						this -> value.push_back(a);
			}
			/**
			  *		@brief	Returns length of number.
			  *		@param	bool include_decimal_length	:
			  *				Optional. Whether include decimal part length.
			  */
			int length (bool include_decimal_length = true)
			{
				if (include_decimal_length)
					return (this -> value.size() + this -> decimal_value.size());
				else
					return this -> value.size();
			}
			/**
			  *		@brief	Sets the number -ve or +ve.
			  *		@param	bool yesno	:	Set -ve Yes/No.
			  */
			void setNegative (bool yesno = true)
			{
				this -> negative = yesno;
			}
			/**
			  *		@brief	Is the number -ve or not.
			  */
			bool isNegative ()
			{
				return this -> negative;
			}
			/**
			  *		@brief	Assigns the number using two (or one) std::list <short int>.
			  *		@param	std::list <short int> num	:	The non-decmal part.
			  *		@param	std::list <short int> dec	:	Optional. The decimal part.
			  */
			void assign (std::list <short int> num, std::list <short int> dec = {})
			{
				auto startN =		num.begin(),
					 terminateN =	num.end();
				auto startD =		dec.begin(),
					 terminateD =	dec.end();

				this -> value.clear();
				bool swtch = false;
				for (; startN != terminateN; startN++)
				{
					if (swtch || *startN != 0)
						swtch = true;
					if (swtch)
						this -> value.push_back(((short int)(*startN)) % 10);
				}
				swtch = false;
				while (terminateD-- != startD)
				{
					if (swtch || *terminateD != 0)
						swtch = true;
					if (swtch)
						this -> decimal_value.push_front(((short int)(*terminateD)) % 10);
				}
			}
			/**
			  *		@brief	Assigns the number using another number.
			  *		@param	ninth_sky::integer_xl ixl	:	Another number.
			  */
			void assign (ninth_sky::integer_xl& ixl)
			{
				this -> value = ixl.value;
				this -> setNegative(ixl.negative);
				this -> decimal_value = ixl.decimal_value;
			}
			/**
			  *		@brief	Refreshes the number. Resolves any error or problem.
			  */
			void refresh ()
			{
				if (this -> value.empty())
				{
					this -> setNegative(false);
					return;
				}

				auto i = this -> value.begin(),
					 l1 = this -> value.end();
				for (; i != l1; i++)
				{
					if (*i == 0)
						this -> value.pop_front();
					else
						break;
				}

				auto j = this -> decimal_value.end(),
					l2 = this -> decimal_value.begin();
				while (j-- != l2)
				{
					if (*j == 0)
						this -> value.pop_front();
					else
						break;
				}
			}
			/**
			  *		@brief	Clears the number.
			  */
			void clear ()
			{
				this -> value.clear();
				this -> setNegative(false);
				this -> decimal_value.clear();
			}
			/**
			  *		@brief	Returns string expression of the number.
			  */
			std::string getString ()
			{
				std::string str;

				auto i = this -> value.begin(),
					 l1 = this -> value.end();
				for (; i != l1; i++)
					str += std::to_string (*i);

				auto j = this -> decimal_value.begin(),
					l2 = this -> decimal_value.end();
				str += ".";
				for (; j != l2; j++)
					str += std::to_string (*j);

				return str;
			}
			/**
			  *		@brief	Checks if the number is empty/null.
			  */
			bool empty ()
			{
				if (this -> value.empty() && this -> decimal_value.empty())
					return true;
				else
					return false;
			}
			/**
			  *		@brief	Reverses the number.
			  */
			void reverse ()
			{
				std::list <short int> tmp;
				tmp = this -> value;
				this -> value = this -> decimal_value;
				this -> decimal_value = tmp;
				this -> value.reverse();
				this -> decimal_value.reverse();
			}

			/**
			  *   @brief  Assignment Operators
			  */
			/**
			  *		@brief		'=' operator
			  */
			void operator = (const std::string number)
			{
				short int magic_number = 48;	  /// used to convert char to int

				this -> value.clear();
				this -> negative = false;
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
			void operator = (long long int lli)
			{
				this -> clear();
				int digit;
				do
				{
					digit = lli % 10;
					this -> appendLeft(digit);
					lli /= 10;

				} while (lli > 0);
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
				*					   +ve - +ve
				*					   +ve - -ve
				*					   -ve - +ve
				*					   -ve - -ve
				*/

				if (ths.isNegative() == false)
				{
					if (ixl.isNegative() == false)
					{
						//ninth_sky::error_report.debug_write("case 1");
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
						//ninth_sky::error_report.debug_write("case 2");
						/// x - -y = x+y

						ixl.setNegative (false);
						answer = ths + ixl;
					}
				}
				else
				{
					if (ixl.isNegative() == false)
					{
						//ninth_sky::error_report.debug_write("case 3");
						/// -x - y = -(x+y)

						ths.setNegative (false);
						answer = ths + ixl;
						answer.setNegative (true);
					}
					else
					{
						//ninth_sky::error_report.debug_write("case 4");
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

					//ninth_sky::error_report.debug_write(tmp); /// debug
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
						tmp = ((*i)*(*j)) + carry;
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
					if (carry != 0)
					{
						_ixl.appendLeft(carry);
						carry = 0;
					}
					/*ninth_sky::error_report.debug_writer_enabled = true;
					ninth_sky::error_report.debug_write(_ixl);
					ninth_sky::error_report.debug_writer_enabled = false;*/
					answer += _ixl;
					_ixl.clear();
					j = ixl.value.end();
				}

				if (this -> negative != ixl.negative)
					answer.setNegative();
				answer.refresh();
				return answer;
			}
			void operator *= (const integer_xl& ixl)
			{
				integer_xl answer, ths;
				ths.assign(this -> value);
				ths.setNegative(this -> negative);
				answer = ths * ixl;
				this -> assign(answer);
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

	/**
	  *		@brief		This class is a scientific data type with extremely
	  *					large values which are Rational (Q) instead of
	  *					integer (Z). It is derived from integer_xl.
	  */
	class rational_xl: public integer_xl, public object
	{
		protected:
			/// under constant construct and demolition...
		public:
			/// under construction...
	};
}


#endif
