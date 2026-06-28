#include <iostream>

int main()
{
    using namespace std;
    int *p = new int[10];
    p[0] = 100;
    p[1] = 200;
    p[2] = 300;
    cout << "p[0] is " << p[0] << endl;
    cout << "p[1] is " << p[1] << endl;
    p = p + 1;
    cout << "Now p[0] is " << p[0] << endl;
    cout << "Now p[1] is " << p[1] << endl;

    delete[] (p - 1);

    short tell[10];
    tell[0] = 1000;
    tell[1] = 2000;
    tell[2] = 3000;
    cout << "tell is " << tell << endl;
    cout << "tell's address is " << &tell << endl;
    // tell ++; Not Allow
    short (*q)[10] = &tell;
    cout << "q is " << q << endl;
    cout << "++q is" << ++q << endl;
    cout << "sizeof(q) is: " << sizeof(q) << endl;
    cout << "sizeof(tell) is: " << sizeof(tell) << endl;
    return 0;
} 