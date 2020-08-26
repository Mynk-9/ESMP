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

    cout << "Segment tree working correct.\n";
}

void test_largeint()
{
    cout << "Testing largeint\n";

    // binary number  100110
    esmp::largeint lint1(vector<bool>{0, 1, 1, 0, 0, 1});
    // binary number 1100011
    esmp::largeint lint2(vector<bool>{1, 1, 0, 0, 0, 1, 1});

    esmp::largeint lint3(lint1 + lint2);
    esmp::largeint lint4(lint1 | lint2);
    esmp::largeint lint5(lint1 & lint2);
    esmp::largeint lint6(lint1 ^ lint2);
    lint3.set_output_base10(false);
    lint4.set_output_base10(false);
    lint5.set_output_base10(false);
    lint6.set_output_base10(false);

    //  100110
    // 1100011

    cout << lint3 << "\n"; // output should be: 10001001
    cout << lint4 << "\n"; // output should be: 1100111
    cout << lint5 << "\n"; // output should be:  100010
    cout << lint6 << "\n"; // output should be: 1000101
    cout << "Successfull - 1.\n";

    // binary number:   101
    // 2's complement:  011
    // sum:            1000
    esmp::largeint lint7(vector<bool>{1, 0, 1});
    esmp::largeint lint8, lint9;
    lint8 = lint7;
    lint8.set_negative(true);
    lint9 = lint7 + lint8;
    lint9.set_output_base10(false);

    cout << lint9 << "\n";
}

int main()
{
    test_integer_xl();
    test_segment_tree();
    test_largeint();

    cout << endl;

    return 0;
}
