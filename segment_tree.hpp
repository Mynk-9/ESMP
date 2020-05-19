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

#include "error_submission.hpp"

#ifndef SEGMENTTREE_ESMP
#define SEGMENTTREE_ESMP


#include <vector>
#include <math.h>
#include <functional>

#include "algo.hpp"

namespace esmp
{
    template <class T>
    class node
    {
    public:
        bool isNullNode = false;    /// used as a filler node at lowest level to complete the tree
        T value;                    /// value contained in the node

        node()
        {
            isNullNode = true;
        }
        node(T val)
        {
            value = val;
        }
        node(const node<T> &_node)
        {
            value = _node.value;
            isNullNode = _node.isNullNode;
        }
    };

    template <class T>
    class segment_tree
    {
    public:
        std::vector< node<T> > tree;           /// index starting from 1
        /// the comparision function to be used in operate
        std::function<T(const T &x, const T &y)> compare;

        /**
         *  @brief  Constructor for segment tree.
         *  @param  const std::vector &base :   std::vector of the T datatype of node
         *                                   for base nodes, i.e., lowest level, i.e.,
         *                                   terminal nodes.
         *  @param   std::function<T(const T &x, const T &y)> compareFunction:
         *                         comparision function taking two
         *                         inputs and giving output of 
         *                         type T.
         * */
        segment_tree(const std::vector<T> &base, 
            std::function<T(const T &x, const T &y)> compareFunction)
        {
            /// 2 * 2 ^ { floor( log2( base size ) ) + 1 }
            //int tree_size = esmp::power(2, (int)(std::log2(base.size())+1));    
            int tree_size = 2*esmp::nextPowerOf2<int>(base.size());           /// size of complete tree vector
            tree.resize(tree_size);

            /// inserting lowest nodes
            for (int i = 0; i < base.size(); i++)
            {
                tree[i+tree_size/2] = node<T> (base[i]);
            }
            /// inserting dummy nodes if any vacancy
            for (int i = base.size(); i < tree_size/2; i++)
            {
                tree[i+tree_size/2] = node<T> ();
            }

            compare = compareFunction;
        }

        /**
         * @brief   recursively build the subtree of the provided index.
         * @param   int i   :   index of the node from which build starts.
         * */
        node<T> build(int i)
        {
            if (i >= tree.size()/2)
                return tree[i];
            else
                tree[i] = 
                    node<T> (operate(build(child(i)), build(child(i)+1)));
            return tree[i];
        }

        node<T> operate(const node<T> &a, const node<T> &b)
        {
            if (a.isNullNode && b.isNullNode)
                return node<T> ();
            else if (a.isNullNode)
                return b;
            else if (b.isNullNode)
                return a;
            else
                return node<T> (compare(a.value, b.value));
        }
        
        /**
         * @brief   Returns child of given node.
         * @param   int i   :   index of given node.
         * @return  index of child node.
         * */
        inline int child(int i)
        {
            return i*2;
        }

        /**
         * @brief   Returns parent of given node.
         * @param   int i   :   index of given node.
         * @return  index of parent node.
         * */
        inline int parent(int i)
        {
            return i/2;
        }

        /**
         * @brief   return root of the segment tree.
         * */
        inline int root()
        {
            return 1;
        }
    };
}

#endif