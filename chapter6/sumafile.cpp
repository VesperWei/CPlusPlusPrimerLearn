#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

int main()
{
    string filename;
    ifstream inFile;

    cout << "Enter filename: ";
    getline(cin, filename);

    inFile.open(filename);
    if (!inFile.is_open())
    {
        cout << "Could not open " << filename << endl;
        exit(EXIT_FAILURE);     //立即终止程序，不会调用局部变量的析构函数，而return方式是会调用析构函数的,例如上面string变量的析构函数
    }

    double value;
    double total_sum = 0.0;
    int count = 0;

    #if 0
    inFile >> value;
    while(inFile.good())
    {
        ++count;
        total_sum += value;
        inFile >> value;
    }
    #endif

    // 与上面注释的代码等价
    while (inFile >> value)
    {
        ++count;
        total_sum += value;
    }

    if (inFile.eof())
    {
        cout << "End of file.\n";
    }
    else if (inFile.fail())     // failbit 或 badbit 被设置（此处已排除 EOF，故为类型不匹配等读取错误）
    {
        cout << "Input terminated by data mismatch.\n";
    }
    else
    {
        cout << "Input terminated by unknown reason.\n";
    }
    inFile.close();

    if (count == 0)
    {
        cout << "No data." << endl;
    }
    else
    {
        cout << "Sum: " << total_sum << endl;
    }

    return 0;
}