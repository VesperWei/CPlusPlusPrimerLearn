// ourfunc.cpp -- define your own function
#include <iostream>

using namespace std;

void simon(int n)
{
    cout << "Simon says touch your toes " << n << " times." << endl;
}

int main()
{
    int count;

    simon(3);
    cout << "Pick an integer: ";
    cin >> count;
    simon(count);
    cout << "Done!" << endl;

    return 0;
}