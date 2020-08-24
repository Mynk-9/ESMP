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

#ifndef LARGEINT_ESMP
#define LARGEINT_ESMP

#include <vector>
#include <functional>

namespace esmp
{

    /**
     * How the std::vector<bool> is used to store binary:
     * binary num:           0 1 0 1 0 0 1 0 0
     * vector indices:       8 7 6 5 4 3 2 1 0
     * */
    class largeint
    {
    private:
        typedef std::vector<bool> binary;

        binary _internal_bin;
        int _size;
        bool _bin_changed = false;
        bool _print_base10 = true;
        std::vector<short int> _base10;

        void _init_binary()
        {
            int i;
            for (i = _internal_bin.size() - 1; i >= 0; --i)
                if (_internal_bin[i])
                    break;
            _size = i + 1;
            _internal_bin.resize(_size);
        }
        binary _operate_on_binary_vectors(const binary &a, const binary &b, std::function<bool(bool, bool)> operation)
        {
            int itr, size;
            if (a.size() > b.size())
            {
                itr = b.size();
                size = a.size();
            }
            else
            {
                itr = a.size();
                size = b.size();
            }

            binary _bin_new(size, 0);
            for (int i = 0; i < itr; ++i)
                _bin_new[i] = operation(b[i], a[i]);
            if (size == a.size())
                for (int i = itr; i < size; ++i)
                    _bin_new[i] = operation(a[i], 0);
            else
                for (int i = itr; i < size; ++i)
                    _bin_new[i] = operation(b[i], 0);
            return _bin_new;
        }

    public:
        /**
         * @brief Initializer with lValue arg
         * @param   binary  binary representation of the number as
         *                  std::vector<bool> lValue
         * */
        largeint(const binary &binary)
        {
            _internal_bin = binary;
            _init_binary();
            _bin_changed = true;
        }

        /**
         * @brief Initializer with rValue arg
         * @param   binary  binary representation of the number as
         *                  std::vector<bool> rValue
         * */
        largeint(binary &&binary)
        {
            _internal_bin = binary;
            _init_binary();
            _bin_changed = true;
        }

        /**
         * @brief Initializer with rValue arg
         * @param   n  lValue largeint 
         * */
        largeint(const largeint &n)
        {
            _internal_bin = n._internal_bin;
            _size = n._size;
            _bin_changed = true;
            _print_base10 = n._print_base10;
        }

        /**
         * @brief Initializer with rValue arg
         * @param   n rValue largeint
         * */
        largeint(largeint &&n)
        {
            _internal_bin = n._internal_bin;
            _size = n._size;
            _bin_changed = true;
            _print_base10 = n._print_base10;
        }

        /**
         * @brief Sets the base in which the number should be 
         *        should be outputted with a << operator.
         *        The base would be 10 or 2.
         * @param   set     bool value to set the base 10 if true,
         *                  2 if false.
         * */
        inline void set_output_base10(bool set)
        {
            _print_base10 = set;
        }

        /**
         * @brief Operator overload for =
         * */
        void operator=(const largeint &n)
        {
            _internal_bin = n._internal_bin;
            _size = n._size;
            _bin_changed = true;
            _print_base10 = n._print_base10;
        }

        /**
         * @brief Operator overload for |
         * */
        largeint operator|(const largeint &n)
        {
            largeint _largeint(
                std::move(_operate_on_binary_vectors(_internal_bin, n._internal_bin, [](bool a, bool b) { return a | b; })));
            return _largeint;
        }

        /**
         * @brief Operator overload for &
         * */
        largeint operator&(const largeint &n)
        {
            largeint _largeint(
                std::move(_operate_on_binary_vectors(_internal_bin, n._internal_bin, [](bool a, bool b) { return a & b; })));
            return _largeint;
        }

        /**
         * @brief Operator overload for ^
         * */
        largeint operator^(const largeint &n)
        {
            largeint _largeint(
                std::move(_operate_on_binary_vectors(_internal_bin, n._internal_bin, [](bool a, bool b) { return a ^ b; })));
            return _largeint;
        }

        /**
         * @brief Operator overload for +
         * */
        largeint operator+(largeint &n)
        {
            int size, tmp;
            binary *l;
            if (n._size > _size)
            {
                size = n._size;
                tmp = _size;
                l = &n._internal_bin;
            }
            else
            {
                size = _size;
                tmp = n._size;
                l = &_internal_bin;
            }
            binary _bin(size + 1);
            int carry = 0;
            int curr = 0;

            for (int i = 0; i < tmp; ++i)
            {
                curr = carry + n._internal_bin[i] + _internal_bin[i];
                carry = 0;
                switch (curr)
                {
                case 0:
                    _bin[i] = 0;
                    break;
                case 1:
                    _bin[i] = 1;
                    break;
                case 2:
                    _bin[i] = 0;
                    carry = 1;
                    break;
                case 3:
                    _bin[i] = 1;
                    carry = 1;
                    break;
                }
            }
            for (int i = tmp; i < size; ++i)
            {
                curr = carry + (*l)[i];
                carry = 0;
                switch (curr)
                {
                case 0:
                    _bin[i] = 0;
                    break;
                case 1:
                    _bin[i] = 1;
                    break;
                case 2:
                    _bin[i] = 0;
                    carry = 1;
                    break;
                }
            }
            _bin[size] = carry;

            return largeint(_bin);
        }

        /// I/O overloads

        /**
         * @brief Operator overload for << out stream
         * */
        friend std::ostream &operator<<(std::ostream &out, const largeint &n)
        {
            if (!n._print_base10)
            {
                for (int i = n._size - 1; i >= 0; --i)
                    out << n._internal_bin[i];
            }

            return out;
        }
    };

} // namespace esmp

#endif