// limits.cpp -- print some interger limits
#include <iostream>
#include <climits>

int main()
{
    using namespace std;
    int n_int_max = INT_MAX;
    short n_short_max = SHRT_MAX;
    long n_long_max = LONG_MAX;
    long long n_llong_max = LLONG_MAX;

    int n_int_min = INT_MIN;
    short n_short_min = SHRT_MIN;
    long n_long_min = LONG_MIN;
    long long n_llong_min = LLONG_MIN;

    cout << "int is" << sizeof(int) << "bytes, "
         << "Max value is " << n_int_max << ", "
         << "Min value is " << n_int_min << ".\n";
    cout << "short is" << sizeof(short) << "bytes, " 
         << "Max value is " << n_short_max << ", "
         << "Min value is " << n_short_min << ".\n";
    cout << "long is" << sizeof(long) << "bytes, " 
         << "Max value is " << n_long_max  << ", "
         << "Min value is " << n_long_min << ".\n";
    cout << "long long is" << sizeof(long long) << "bytes, " 
         << "Max value is " << n_llong_max << ", "
         << "Min value is " << n_llong_min << ".\n";

    cout << "unsigned long long is" << sizeof(unsigned long long) << "bytes, "
         << "Max value is " << ULLONG_MAX << ".\n";
    cout << "Is ULLONG_MAX == 2 * LLONG_MAX + 1 ? "
         << ((ULLONG_MAX == (2 * (unsigned long long)LLONG_MAX + 1)) ? "true" : "false") 
         << ".\n";
    cout << "Bits per byte" << CHAR_BIT << ".\n";
    return 0;
}