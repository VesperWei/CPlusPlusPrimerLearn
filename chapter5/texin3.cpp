#include <iostream>

int main()
{
    using namespace std;
    char ch;
    int count = 0;

    cin.get(ch);
    while (cin)
    //while (false == cin.fail())
    {
        cout.put(ch);
        // 另一种等价的方式
        //cout << ch;

        count++;

        // 当函数的参数声明为引用，就可以修改传入的变量，比如下面的ch，这在C中是做不到的。返回类型是istream对象
        cin.get(ch);
        // 另一种等价的方式，返回值为int类型的字符编码
        // ch = cin.get();
        // 以下方式会忽略空格、换行符、制表符，不建议用
        // cin >> ch;
    }

    cout << count << " chars read\n";
    return 0;
}