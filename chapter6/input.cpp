#include <iostream>
#include <limits>
#include <sstream>
#include <string>

// 将空格、换行等不可见字符以便于观察的形式打印出来
void printCharacter(int c)
{
    if (c == EOF)
    {
        std::cout << "EOF";
        return;
    }

    switch (c)
    {
        case '\n':
            std::cout << R"('\n')";
            break;

        case '\t':
            std::cout << R"('\t')";
            break;

        case ' ':
            std::cout << "' '（空格）";
            break;

        default:
            std::cout << '\'' << static_cast<char>(c) << '\'';
            break;
    }
}

// 丢弃当前输入行中尚未读取的所有字符，包括最后的换行符
void discardCurrentLine()
{
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );
}

// 演示 cin >> 的格式化输入
void demoFormattedInput()
{
    std::cout << "\n========== 1. cin >> 格式化输入 ==========\n";

    int number;
    char option;

    std::cout << "请输入一个整数和一个字符，例如：123 A\n> ";

    /*
     * operator>> 会根据变量类型解析输入：
     *
     * 1. 读取前先跳过空格、Tab、换行等前导空白；
     * 2. number 按整数格式读取；
     * 3. option 按字符格式读取；
     * 4. 读取完成后的空格或换行通常仍留在输入流中。
     */
    if (!(std::cin >> number >> option))
    {
        std::cout << "输入格式错误。\n";

        // 清除 failbit，让 cin 恢复可用状态
        std::cin.clear();

        // 丢弃本行中的错误输入
        discardCurrentLine();
        return;
    }

    std::cout << "读取到的整数：" << number << '\n';
    std::cout << "读取到的字符：" << option << '\n';

    /*
     * peek() 查看下一个字符，但不取走它。
     *
     * 如果输入的是：
     *     123 A<回车>
     *
     * 那么读取 A 后，下一个字符通常是 '\n'。
     */
    std::cout << "读取完成后，输入流中的下一个字符是：";
    printCharacter(std::cin.peek());
    std::cout << '\n';

    /*
     * 清除这一行剩余的空格和换行。
     *
     * 如果不清除，后面的 cin.get() 可能立即读到这里残留的 '\n'。
     */
    discardCurrentLine();
}

// 演示 cin.get() 和 cin.get(char&)
void demoGetOneCharacter()
{
    std::cout << "\n========== 2. cin.get() 读取单个字符 ==========\n";

    std::cout << "请输入一行内容，可以尝试让第一个字符为空格：\n> ";

    /*
     * 无参数 get() 返回 int，而不是 char。
     *
     * 这样既能返回所有可能的字符值，也能使用 EOF 表示输入结束。
     *
     * get() 不会跳过空白，因此空格、Tab、换行都可以被读取。
     */
    int c = std::cin.get();

    if (c == EOF)
    {
        std::cout << "遇到 EOF。\n";
        return;
    }

    std::cout << "cin.get() 读取到：";
    printCharacter(c);
    std::cout << '\n';

    /*
     * get() 只读取了一个字符。
     * 如果这一行还有其他字符，将其丢弃，避免影响后面的示例。
     *
     * 如果读取到的本身就是 '\n'，则不需要再次 ignore，
     * 否则 ignore 会等待下一行输入。
     */
    if (c != '\n')
    {
        discardCurrentLine();
    }

    std::cout << "\n再输入一行内容：\n> ";

    char ch;

    /*
     * 带 char& 参数的重载版本。
     *
     * 作用与无参数 get() 类似，但读取结果直接写入 ch。
     * 返回值是 std::istream&，可以用来判断读取是否成功。
     */
    if (std::cin.get(ch))
    {
        std::cout << "cin.get(ch) 读取到：";
        printCharacter(static_cast<unsigned char>(ch));
        std::cout << '\n';

        if (ch != '\n')
        {
            discardCurrentLine();
        }
    }
    else
    {
        std::cout << "读取失败。\n";
    }
}

// 演示 cin.get(char*, size)
void demoGetCharacterArray()
{
    std::cout << "\n========== 3. cin.get(buffer, size) ==========\n";

    char buffer[8]{};

    std::cout << "请输入一行内容，最多保存7个字符：\n> ";

    /*
     * buffer 的总容量是8：
     *
     *   最多保存7个有效字符；
     *   最后一个位置用于保存字符串结束符 '\0'。
     *
     * get(buffer, size) 遇到换行符时停止，
     * 但是不会取走这个换行符。
     */
    std::cin.get(buffer, sizeof(buffer));

    /*
     * 如果用户直接按回车，get() 没有提取到字符，
     * 输入流可能进入 fail 状态。
     */
    if (std::cin.fail() && !std::cin.eof())
    {
        std::cout << "没有读取到有效字符，可能输入的是空行。\n";
        std::cin.clear();
    }
    else
    {
        std::cout << "buffer 中的内容：\"" << buffer << "\"\n";
    }

    std::cout << "get() 结束后，下一个字符是：";
    printCharacter(std::cin.peek());
    std::cout << '\n';

    /*
     * get(buffer, size) 不会取走分隔符。
     *
     * 如果输入内容超过7个字符，输入流中还会残留未读取的普通字符；
     * 如果未超过长度，通常残留的是换行符。
     */
    discardCurrentLine();
}

// 演示 cin.getline()
void demoCinGetline()
{
    std::cout << "\n========== 4. cin.getline() ==========\n";

    char buffer[8]{};

    std::cout << "请输入一行内容，最多保存7个字符：\n> ";

    /*
     * cin.getline() 用于读取 C 风格字符串 char[]。
     *
     * 与 cin.get(buffer, size) 的重要区别：
     *
     *   get()     遇到换行后停止，但换行仍留在输入流中；
     *   getline() 遇到换行后停止，并取走、丢弃换行符。
     */
    std::cin.getline(buffer, sizeof(buffer));

    if (std::cin.fail())
    {
        /*
         * 输入内容超过数组容量时，getline() 会设置 failbit。
         *
         * 此时必须：
         * 1. clear() 清除错误状态；
         * 2. ignore() 丢弃这一行剩余内容。
         *
         * 否则后面的输入操作将继续失败。
         */
        std::cout << "输入内容太长，字符数组无法完整保存。\n";

        std::cin.clear();
        discardCurrentLine();
    }
    else
    {
        std::cout << "buffer 中的内容：\"" << buffer << "\"\n";

        /*
         * 正常情况下，getline() 已经取走并丢弃了换行符，
         * 因此这里不需要再调用 ignore()。
         */
    }
}

// 演示 std::getline()
void demoStdGetline()
{
    std::cout << "\n========== 5. std::getline(cin, string) ==========\n";

    std::string line;

    std::cout << "请输入任意长度的一行文本，可以包含空格：\n> ";

    /*
     * std::getline() 是非成员函数，接收 std::string。
     *
     * 与 cin.getline() 相比：
     *
     *   cin.getline()        保存到固定长度的 char[]；
     *   std::getline()       保存到可自动扩展的 std::string。
     *
     * 两者都会读取并丢弃默认分隔符 '\n'。
     */
    if (std::getline(std::cin, line))
    {
        std::cout << "读取到的内容：\"" << line << "\"\n";
        std::cout << "字符串长度：" << line.size() << '\n';
    }
    else
    {
        std::cout << "读取失败或遇到 EOF。\n";
    }
}

// 演示 cin >> 与 getline 混用时的问题
void demoMixingFormattedAndLineInput()
{
    std::cout << "\n========== 6. cin >> 与 getline() 混用 ==========\n";

    /*
     * 使用 istringstream 模拟以下标准输入：
     *
     *     18<回车>
     *     Tom Smith<回车>
     *
     * istringstream 也是 istream，因此读取规则与 cin 相同。
     */

    {
        std::istringstream input("18\nTom Smith\n");

        int age;
        std::string name;

        input >> age;

        /*
         * 错误用法：
         *
         * operator>> 读取18后，换行符仍留在输入流中。
         * getline() 会立即遇到这个换行符，因此读取到空字符串。
         */
        std::getline(input, name);

        std::cout << "未使用 ignore()：\n";
        std::cout << "age  = " << age << '\n';
        std::cout << "name = \"" << name << "\"\n";
    }

    {
        std::istringstream input("18\nTom Smith\n");

        int age;
        std::string name;

        input >> age;

        /*
         * 正确用法：
         *
         * 丢弃 operator>> 读取后残留的内容，直到并包括换行符。
         */
        input.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::getline(input, name);

        std::cout << "\n使用 ignore() 后：\n";
        std::cout << "age  = " << age << '\n';
        std::cout << "name = \"" << name << "\"\n";
    }
}

// 演示自定义分隔符
void demoCustomDelimiter()
{
    std::cout << "\n========== 7. 自定义分隔符 ==========\n";

    {
        std::istringstream input("apple,banana");
        char buffer[16]{};

        /*
         * 第三个参数 ',' 表示读取到逗号为止。
         *
         * getline() 会取走并丢弃这个逗号。
         */
        input.getline(buffer, sizeof(buffer), ',');

        std::cout << "cin.getline(buffer, size, ',') 的结果："
                  << buffer << '\n';

        std::string remaining;
        std::getline(input, remaining);

        std::cout << "输入流中剩余内容：" << remaining << '\n';
    }

    {
        std::istringstream input("apple,banana");
        std::string text;

        /*
         * std::getline() 同样可以指定自定义分隔符。
         */
        std::getline(input, text, ',');

        std::cout << "std::getline(input, text, ',') 的结果："
                  << text << '\n';
    }
}

int main()
{
    std::cout << "C++ 标准输入函数示例程序\n";

    demoFormattedInput();
    demoGetOneCharacter();
    demoGetCharacterArray();
    demoCinGetline();
    demoStdGetline();
    demoMixingFormattedAndLineInput();
    demoCustomDelimiter();

    std::cout << "\n========== 示例结束 ==========\n";

    return 0;
}