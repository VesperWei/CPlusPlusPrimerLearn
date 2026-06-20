#include <iostream>
using namespace std;

int main()
{
    cout << "What year was your house built?\n";
    int year;
    cin >> year;
    cin.get();
    cout << "What is its street address?\n";
    char address[80];
    cin.getline(address, 80);
    cout << "You live at " << address << ".\n";
    return 0;
}