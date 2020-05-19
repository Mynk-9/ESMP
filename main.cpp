#include <iostream>
#include <vector>

#include "ESMP.hpp"

using namespace std;

int main()
{
    cout << "ESMP compiled successfully." << endl;
    esmp::integer_xl a, b, c;
    
    a = 5;
    b = 5;
    c = 6;
    cout << (a + b) << " " << c << endl;
    cout << "integer_xl working correct.\n";

    esmp::segment_tree<int> seg(vector<int>{1, 2, 3, 4, 5}, [](const int &x, const int &y) { return x + y; });
    for (int i = 1; i < seg.tree.size(); i++)
        (!seg.tree[i].isNullNode ? (std::cout << seg.tree[i].value << ", ") : (std::cout << "~, "));
    std::cout << endl;
    seg.build(seg.root());
    for (int i = 1; i < seg.tree.size(); i++)
        (!seg.tree[i].isNullNode ? (std::cout << seg.tree[i].value << ", ") : (std::cout << "~, "));
    std::cout << endl;

    vector<vector<int>> temp = {{1, 2}, {3, 4, 5}, {6, 7}};
    esmp::segment_tree<vector<int>> seg_vec(temp, [](const vector<int> a, const vector<int> b) {
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
    });
    seg_vec.build(seg_vec.root());

    for (int i = 1; i < seg_vec.tree.size(); i++)
    {
        if (seg_vec.tree[i].isNullNode == false)
        {
            cout << "{";
            for (int p : seg_vec.tree[i].value)
                cout << p << " ";
            cout << "}, ";
        }
        else
        {
            cout << "~, ";
        }
    }
    cout << "\nsegment tree working correct.\n";
    std::cout << endl;

    return 0;
}
