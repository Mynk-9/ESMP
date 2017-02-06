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
	*	@brief		This class include a scientific data type with extremely large
					possible value calculations.
	*/
	class integer_xl
	{
		private:
			std::list <short int> value;
			short int magic_number = 48;      /// used to convert char to int
			bool negative = false;

		public:
			void appendLeft (int a)
			{
				this -> value.push_front(a);
			}
			int length ()
			{
				return this -> value.size();
			}
			void setNegative (bool yesno)
			{
			    if (!this -> value.empty())
                    this -> negative = yesno;
			}
			void assign (std::list <short int> lst)
			{
			    auto start =        lst.begin(),
                     terminate =    lst.end();
			    /*try
			    {
			        bool lambda = ((*start)/15);
			    }
			    catch (int ex)
			    {
			        std::string err = "Error at assignment of the integer_xl. Non number data types are not allowed.\n";
			        err += "Error catch report: \n";
			        err += "caught @ integer_xl.assign method.\n";
			        err += "value passed (std::list <[non-integer(type unknown)]>) : \n";
			        for (; start != terminate; start++)
                        err += *start + "\n";
                    err += "\ncurrent value of the integer: \n";
                    auto z = this -> value.begin();
                    for (; z != this -> value.end(); z++)
                        err += *z + "\n";
                    err += "\n++++++++++++++++++++";

			        ninth_sky::error_report.submit_error(err);
			        return;
			    }*/

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

			/**
			*   @brief  assignment operators
			*/
			void operator = (const std::string number)
			{
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
			}

			/**
			*   @brief  relational operators
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
			*   @brief  arithmetic operators
			*/
			/*integer_xl operator - (const integer_xl& ixl2)
			{
			    integer_xl ixl1, answer;
			    ixl1.assign(this -> value);
			    if (ixl2 > ixl1)
                {
                    integer_xl tmp;
                    tmp = ixl1;
                    ixl1 = ixl2;
                    ixl2 = tmp;
                }
                auto l1 =   ixl1.value.begin(),
                     l2 =   ixl2.value.begin(),
                     i =    ixl1.value.end(),
                     j =    ixl2.value.end();
                bool swtch_i = true, swtch_j = true, carry = 0;
                short int tmp = 0;
                while (swtch_i || swtch_j)
                {
                    tmp = -1 * (int)(carry);
                    if (swtch_i && i-- == l1)
                        swtch_i = false;
                    else
                        tmp = *i;
                    if (swtch_j && j-- == l2)
                        swtch_j = false;
                    else
                        tmp -= *j;

                    if (tmp < 0)
                    {
                        carry = 1;
                        tmp += 10;
                    }
                    ninth_sky::error_report.debug_write(tmp); /// debug
                    answer.appendLeft (tmp);
                    tmp = 0;
                }
                if (*answer.value.begin() == 0)
                    answer.value.pop_front();
			    return answer;
			}*/
			integer_xl operator + (const integer_xl& ixl)
			{
			    /*if (this -> negative != ixl.negative)
			    {
			        integer_xl tmp;
			        tmp.assign(this -> value);
			        if (this -> negative == true)
                        return (ixl - tmp);
                    else
                        return (tmp - ixl);
			    }*/

				integer_xl answer;
				answer.setNegative(this -> negative);

				bool carry =    0,
					 swtch_i =  true,
					 swtch_j =  true;
				int tmp = 0;
				auto i =    this -> value.end();
				auto j =    ixl.value.end();
				auto l1 =   this -> value.begin();
				auto l2 =   ixl.value.begin();

				while (swtch_i || swtch_j)
				{
					tmp += carry;
					if (swtch_i && i-- == l1)
						swtch_i = false;
					else if (swtch_i)
						tmp += *i;
					if (swtch_j && j-- == l2)
						swtch_j = false;
					else if (swtch_j)
						tmp += *j;

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

				if (*(answer.value.begin()) == 0)
					answer.value.pop_front();
				if (carry == 1)
					answer.appendLeft(carry);

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
