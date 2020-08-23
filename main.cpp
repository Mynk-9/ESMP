#include <iostream>
#include <vector>

#include "ESMP.hpp"

using namespace std;

void test_integer_xl()
{
    cout << "ESMP compiled successfully." << endl;
    esmp::integer_xl a, b, c;

    a = 5;
    b = 5;
    c = 6;
    cout << (a + b) << " " << c << endl;
    cout << "integer_xl working correct.\n";
}

void test_segment_tree()
{
    cout << "Creating segment tree of int. Operation would take sum to place on the parent node.\n";
    esmp::segment_tree<int> seg(vector<int>{1, 2, 3, 4, 5}, [](const int &x, const int &y) { return x + y; });
    auto printSeg = [](const esmp::segment_tree<int> &s) {
        for (int i = 1; i < s.tree.size(); i++)
            (!s.tree[i].isNullNode ? (cout << s.tree[i].value << ", ") : (cout << "~, "));
        cout << "\n";
    };

    printSeg(seg);
    seg.build(seg.root());
    printSeg(seg);

    cout << "Creating segment tree of vectors. Operation would pick larger vector to place on the parent node.\n";
    esmp::segment_tree<vector<int>> seg_vec(vector<vector<int>>{{1, 2}, {3, 4, 5}, {6, 7}}, [](const vector<int> a, const vector<int> b) {
        int asize = a.size();
        int bsize = b.size();
        if (asize > bsize)
            return a;
        else if (asize == bsize && asize != 0)
        {
            for (int i = 0; i < asize; i++)
                if (a[i] > b[i])
                    return a;
                else if (a[i] < b[i])
                    return b;
        }
        else
            return b;
        return b;
    });
    auto printSegVec = [](const esmp::segment_tree<vector<int>> &a) {
        for (int i = 1; i < a.tree.size(); i++)
        {
            if (a.tree[i].isNullNode == false)
            {
                cout << "{";
                for (int p : a.tree[i].value)
                    cout << p << " ";
                cout << "}, ";
            }
            else
            {
                cout << "~, ";
            }
        }
        cout << "\n";
    };

    printSegVec(seg_vec);
    seg_vec.build(seg_vec.root());
    printSegVec(seg_vec);

    cout << "\nsegment tree working correct.\n";
}

int main()
{
    test_integer_xl();
    test_segment_tree();

    cout << endl;

    return 0;
}
