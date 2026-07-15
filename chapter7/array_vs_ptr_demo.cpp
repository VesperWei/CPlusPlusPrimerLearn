// array_vs_ptr_demo.cpp
// 演示 array 与 &array[0] 的相同点和差异点

#include <iostream>

const int N = 5;

// 接收 int* 的普通函数
void print_via_ptr(const int* p, int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}

// ============================================================
// 相同点
// ============================================================

void test_same_value()
{
    std::cout << "========== 相同点1：值上相等 ==========\n";

    int array[N] = {10, 20, 30, 40, 50};

    // array 在大多数表达式中会"退化"为指向首元素的指针，
    // 因此 array 与 &array[0] 得到的是同一个地址。
    int* p1 = array;
    int* p2 = &array[0];

    std::cout << "    array      = " << p1 << '\n';
    std::cout << "    &array[0]  = " << p2 << '\n';
    std::cout << "    p1 == p2   = " << (p1 == p2) << " （值相等）\n";
}

void test_same_arithmetic()
{
    std::cout << "\n========== 相同点2：指针运算等价 ==========\n";

    int array[N] = {10, 20, 30, 40, 50};

    // 两者做指针加减、下标访问，结果完全一致。
    std::cout << "    *(array + 2)     = " << *(array + 2)     << '\n';
    std::cout << "    *(&array[0] + 2) = " << *(&array[0] + 2) << '\n';
    std::cout << "    array[2]         = " << array[2]         << '\n';
}

void test_same_function_arg()
{
    std::cout << "\n========== 相同点3：作为函数参数等价 ==========\n";

    int array[N] = {10, 20, 30, 40, 50};

    // 传给函数时，array 自动退化为 int*，
    // 与显式传 &array[0] 效果完全相同。
    std::cout << "    传 array:     "; print_via_ptr(array, N);
    std::cout << "    传 &array[0]: "; print_via_ptr(&array[0], N);
}

// ============================================================
// 差异点
// ============================================================

void test_diff_sizeof()
{
    std::cout << "\n========== 差异1：sizeof 结果不同 ==========\n";

    int array[N] = {10, 20, 30, 40, 50};
    int* ptr     = array;   // ptr 是真正的指针变量，类型为 int*

    // sizeof(array) 计算整个数组占用的字节数；
    // sizeof(ptr)   只计算指针变量自身占用的字节数。
    std::cout << "    sizeof(array) = " << sizeof(array)
              << "  （整个数组，" << N << " 个 int）\n";
    std::cout << "    sizeof(ptr)   = " << sizeof(ptr)
              << "  （指针本身）\n";
}

void test_diff_addressof_type()
{
    std::cout << "\n========== 差异2：& 取地址后类型不同 ==========\n";

    int array[N];

    // &array    的类型是 int(*)[N]，即"指向整个数组的指针"；
    // &array[0] 的类型是 int*，     即"指向单个 int 的指针"。
    int(*parr)[N] = &array;     // ✅ 类型匹配
    int* pint     = &array[0];   // ✅ 类型匹配

    std::cout << "    &array     类型：int(*)[" << N << "]\n";
    std::cout << "    &array[0]  类型：int*\n";

    // 两个地址值相同，但 +1 时跳过的字节数截然不同。
    // 这里用 char* 做减法，是为了按"字节"统计跨度。
    std::cout << "    &array + 1     跳过 "
              << (reinterpret_cast<char*>(parr + 1) - reinterpret_cast<char*>(parr))
              << " 字节（整个数组）\n";
    std::cout << "    &array[0] + 1  跳过 "
              << (reinterpret_cast<char*>(pint + 1) - reinterpret_cast<char*>(pint))
              << " 字节（1 个 int）\n";
}

void test_diff_assignability()
{
    std::cout << "\n========== 差异3：能否被修改 ==========\n";

    int array[N] = {10, 20, 30, 40, 50};

    // array 是数组名，不是可修改的左值，不能赋值也不能自增：
    //     array = nullptr;   // ❌ 编译错误
    //     array++;           // ❌ 编译错误

    // 而 &array[0] 赋给指针变量后，该指针可以自由修改。
    int* ptr = &array[0];
    std::cout << "    初始 ptr 指向 array[0]，*ptr = " << *ptr << '\n';

    ptr++;   // ✅ 指针可以自增
    std::cout << "    ptr++ 后指向 array[1]，*ptr = " << *ptr << '\n';

    ptr = nullptr;   // ✅ 指针可以重新赋值
    std::cout << "    ptr = nullptr 后，ptr = " << ptr << '\n';
}

int main()
{
    std::cout << "array 与 &array[0] 的相同点与差异点演示\n\n";

    // --- 相同点 ---
    test_same_value();
    test_same_arithmetic();
    test_same_function_arg();

    // --- 差异点 ---
    test_diff_sizeof();
    test_diff_addressof_type();
    test_diff_assignability();

    std::cout << "\n========== 演示结束 ==========\n";
    return 0;
}
