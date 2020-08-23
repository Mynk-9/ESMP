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
        largeint(const binary &binary)
        {
            _internal_bin = binary;
            _init_binary();
        }
        largeint(const binary &&binary)
        {
            _internal_bin = binary;
            _init_binary();
        }

        largeint operator|(const largeint &n)
        {
            largeint _largeint(
                std::move(_operate_on_binary_vectors(_internal_bin, n._internal_bin, [](bool a, bool b) { return a | b; })));
            return _largeint;
        }
        largeint operator&(const largeint &n)
        {
            largeint _largeint(
                std::move(_operate_on_binary_vectors(_internal_bin, n._internal_bin, [](bool a, bool b) { return a & b; })));
            return _largeint;
        }
        largeint operator^(const largeint &n)
        {
            largeint _largeint(
                std::move(_operate_on_binary_vectors(_internal_bin, n._internal_bin, [](bool a, bool b) { return a ^ b; })));
            return _largeint;
        }
    };

} // namespace esmp

#endif