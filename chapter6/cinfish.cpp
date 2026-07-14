#include <iostream>
#include <limits>
const int MAX = 5;

int main()
{
    using namespace std;

    double fish[MAX];
    double total = 0.0;
    int i = 0;

    cout << "Please enter your weights of your fish.\n";
    cout << "You may enter up to " << MAX << " fishs <q to quit>.\n";

    do
    {
        cout << "Round #" << i + 1 << ": ";
        if (!(cin >> fish[i]))
        {
            if (cin.eof())
            {
                break;   // 输入流结束，干净退出，不再尝试恢复
            }

            //输入内容转目标类型失败后，必须clear，否则读不了后续的数据
            cin.clear();

            // 尝试读一个字符
            char q = '\0';
            if ((cin >> q) && (q == 'q' || q == 'Q'))
            {
                break;
            }

            //丢弃整行的输入流
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //换一种方式丢失整行的输入流
            //string dummy;
            //getline(cin, dummy);

            //换一种方式丢失整行的输入流
            //int c;
            //while ((c = cin.get()) != '\n' && c != EOF) { }

            cout << "Bad input, please try again.\n";
            continue;
        }
        else
        {
            total += fish[i];
            i++;
        }
    } while (i < MAX);

    if (i == 0)
    {
        cout << "No fish\n";
    }
    else
    {
        cout << total / i << " is average weight of " << i << " fish\n";
    }

    return 0;
}