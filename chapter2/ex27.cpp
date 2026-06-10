#include <iostream>

using namespace std;

void printTime(int hours, int minutes, int seconds)
{
    cout << "Time: " << hours << ":" << minutes << ":" << seconds << endl;
}

int main()
{
    cout << "Enter the number of hours:";
    int hours;
    cin >> hours;
    cout << "Enter the number of minutes:";
    int minutes;
    cin >> minutes;
    cout << "Enter the number of seconds:";
    int seconds;
    cin >> seconds;

    printTime(hours, minutes, seconds);
    return 0;
}