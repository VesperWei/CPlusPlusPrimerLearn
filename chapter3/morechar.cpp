#include <iostream>

int main()
{
    using namespace std;

    char ch = 'M';
    int i = ch;

    cout << "The ASCII code for " << ch << " is " << i << endl;
    
    cout << "Add one to character code " << ch << endl;
    ch = ch + 1;
    cout << "Now " << ch << " has code " << int(ch) << endl;
    
    cout << "Displaying char ch using cout.put(ch): ";
    cout.put(ch);
    cout.put('~');
    cout << endl;
    return 0;
}