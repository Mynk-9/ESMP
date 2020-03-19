#include <iostream>

#include "ESMP.hpp"

using namespace std;

int main()
{
    cout << "ESMP compiled successfully." << endl;
    esmp::integer_xl a, b, c;
    cin >> a;
    cin >> b;
    cin >> c;
    cout << (a+b) << " " << c << endl;
    return 0;
}