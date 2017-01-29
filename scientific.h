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
#include <string>

namespace ninth_sky
{
	/**
	*	@brief		This class include a scientific data type with extremely large
					possible value calculations.
	*/
	class extra_long
	{
    private:
        std::list <short int> value;
        short int magic_number = 48;      /// used to convert char to int

    public:
        void appendLeft (int a)
        {
            value.push_front(a);
        }
        int length ()
        {
            return value.size();
        }

        /**
        *   @brief  operators
        */
        void operator = (const std::string number)
        {
            value.clear();
            bool swtch = false;
            for (char c : number)
            {
                short int si = (int)(c - magic_number);
                if (si < 10 && swtch)
                    value.push_back (si);
                else if (!swtch && si != 0 && si < 10)
                {
                    value.push_back (si);
                    swtch = true;
                }
            }
        }
        void operator = (const extra_long exl)
        {
            value = exl.value;
        }
        extra_long operator + (const extra_long& exl)
        {
            extra_long answer;
            bool carry = 0, swtch_i = true, swtch_j = true;
            int tmp = 0;
            auto i = value.end();
            auto j = exl.value.end();
            auto l1 = value.begin();
            auto l2 = exl.value.begin();

            while (swtch_i || swtch_j)
            {
                tmp += carry;
                if (i-- == l1)
                    swtch_i = false;
                else
                    tmp += *i;
                if (j-- == l2)
                    swtch_j = false;
                else
                    tmp += *j;

                if (tmp >= 10)
                {
                    tmp -= 10;
                    carry = 1;
                }
                else
                    carry = 0;

                std::cout << tmp << "\n";

                answer.appendLeft(tmp);
                tmp = 0;
            }
            if (*(answer.value.begin()) == 0)
                answer.value.pop_front();
            if (carry == 1)
                answer.appendLeft(carry);
            return answer;
        }
        friend std::ostream& operator << (std::ostream& out, const extra_long& exl)
        {
            for (auto i = exl.value.begin(); i != exl.value.end(); i++)
                out << (*i);
            out.flush();
        }
        friend std::istream& operator >> (std::istream& in, extra_long& exl)
        {
            std::string str;
            in >> str;
            exl = str;
        }
	};
}


#endif
