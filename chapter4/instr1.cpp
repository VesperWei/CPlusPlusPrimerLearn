#include <iostream>
using namespace std;

int main()
{
    const int ArSize = 20;
    char name[ArSize];
    char dessert[ArSize];

    cout << "Enter your name:\n";
    // 不能使用空格分隔，例如输入Jack Ma，那么Name只会保存Jack，剩余Ma仍在输入缓冲区
    //cin >> name;
    // 读入整行的数据，会丢弃分隔符（如\n）
    cin.getline(name, ArSize);  
    // 与getline的机制相似，但不会丢失分隔符，所以需要再调用一次get()函数读出分隔符
    //cin.get(name, ArSize).get();

    cout << "Enter your favorite dessert:\n";
    cin.getline(dessert, ArSize);
    
    cout << "I have some delicious " << dessert;
    cout << " for you, " << name << ".\n";
    return 0;
}