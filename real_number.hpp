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

#ifndef REALNUM_ESMP
#define REALNUM_ESMP

#include <list>
#include <iterator>
#include <utility>
#include <string>

namespace esmp
{
class real_number
{
private:
    std::list<signed char> num;
    int dec_pos = 0;

public:
    /**
    * Constructors and Destructors
    **/
    real_number();
    real_number(std::string &num);
    template <typename T>
    real_number(T &num);
    ~real_number();

    /**
     * Assignment methods
     * */
    bool set_value(std::string &num);
    template <typename T>
    bool set_value(T &num);
};

real_number::real_number()
{
    dec_pos = 0;
    num.push_back(0);
}

real_number::real_number(std::string &num)
{
    
}

/// T datatype should be std::to_string() compatible.
template <typename T>
real_number::real_number(T &num)
{
    std::string _num = to_string(num);
}

real_number::~real_number()
{
    num.clear();
    dec_pos = 0;
}

bool real_number::set_value(std::string &num)
{
    char x = '0';
    short int dec_pos_correction = 0;
    for (int i = 0; i < num.size(); ++i)
    {
        if (0 <= num[i] - x && num[i] - x <= 9)
            this->num.push_back(num[i] - x);
        else if (num[i] == '.' && dec_pos == 0)
            dec_pos = i;
        else// if (num[i] == '.' && dec_pos != 0)
            ++dec_pos_correction;
    }
    return true;
}

} // namespace esmp

#endif