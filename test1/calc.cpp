#include "calc.h"
#include <iostream>

using namespace std;

int main() {
    int a = 10;
    int b = 5;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << add(a, b) << endl;
    cout << "a - b = " << subtract(a, b) << endl;
    cout << "a * b = " << multiply(a, b) << endl;
    cout << "a / b = " << divide(a, b) << endl;
    return 0;
}