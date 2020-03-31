#include <iostream>

#include "ESMP.hpp"

using namespace std;

int main()
{
    cout << "ESMP compiled successfully." << endl;
    esmp::integer_xl a, b, c;
    /*cin >> a;
    cin >> b;
    cin >> c;*/
    a = 5;
    b = 5;
    c = 6;
    cout << (a+b) << " " << c << endl;
    cout << "integer_xl working correct.";

    esmp::segment_tree<int> seg(vector<int>{1, 2, 3, 4, 5}, [](const int &x, const int &y){return x+y;});
    for (int i = 0; i < seg.tree.size(); i++)
        (!seg.tree[i].isNullNode ? (std::cout << seg.tree[i].value << ", ") : (std::cout << "~, "));
    std::cout << endl;
    seg.build(seg.root());
    for (int i = 1; i < seg.tree.size(); i++)
        (!seg.tree[i].isNullNode ? (std::cout << seg.tree[i].value << ", ") : (std::cout << "~, "));
    std::cout << endl;
    cout << "segment tree working correct."

    return 0;
}