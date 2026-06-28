#include <iostream>

int main()
{
    enum bits { one = 1, two = 2, four = 4, eight = 8 };
    bits myFlag = bits(one | two);
    bits yourFlag = bits(four + eight + 10000);
    std::cout << "myFlag = " << static_cast<int>(myFlag) << std::endl;
    std::cout << "yourFlag = " << static_cast<int>(yourFlag) << std::endl;
    return 0;
}