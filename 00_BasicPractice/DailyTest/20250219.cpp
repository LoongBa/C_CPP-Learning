#include <iostream>
#include <string>
#include <algorithm> // for std::reverse
using namespace std;

// 使用字符串倒序的方法判断回文数，引用代替指针
string reverseString(const string &strNum) // constant 常量 
// 传值：（赋值）传参——复制了一份，不影响调用者的原来的值——函数退出时，自动清理堆栈
// 传址：传指针/引用传参，传的是地址，可以改变调用者的原来的值——函数退出时，不会清理堆栈，否则影响调用者的原来的值
// 防止在函数内部修改原始字符串，可以使用 const 关键字
// 传址：引用传参，传的是地址，可以改变调用者的原来的值；指针传参，传的是指针，可以改变调用者的原来的值
// 引用与指针的区别：
// 引用是一个别名，它指向一个已经存在的变量，而指针是一个变量，它存储了另一个变量的内存的地址。
// 引用在声明时必须初始化，而指针可以在声明时不初始化。
// 引用在声明后不能再改变指向的对象，而指针可以改变指向的对象。
// 引用在定义时必须指定类型，而指针可以不指定类型。
// 指针过于灵活，所以在函数传参时，尽量使用引用，因为引用更加安全。
{
    int len = strNum.length();
    string reversedStr;
    // 初始化内存，避免多次重新分配内存
    reversedStr.reserve(len);       // reserve 预留，reverse 倒序
    for (int i = 0; i < len; i++)
        reversedStr = strNum[i] + reversedStr;
    return reversedStr;
}
// 使用字符串倒序的方法判断回文数，使用指针传参
string reverseStringByPointer(const string *strNum_ptr)
{
    string reversedStr;
    int len = strNum_ptr->length();     // 指针访问成员变量使用 -> 运算符
    // 初始化内存，避免多次重新分配
    reversedStr.reserve(len);
    for (int i = 0; i < len; i++)
        reversedStr = strNum_ptr[i] + reversedStr;
    return reversedStr;
}
// 使用基于范围的 for 循环来反转字符串
string reverseStringRangeBased(const string &strNum)
{
    string reversedStr;
    // 初始化内存，避免多次重新分配内存
    reversedStr.reserve(strNum.size());
    for (char c : strNum) // for in range: 基于范围的循环  类似 Python for in range(5)
        reversedStr = c + reversedStr;

    return reversedStr;
}
// 使用 std::reverse 来反转字符串
string reverseStringBySTL(string reversedStr)
{
    // 需要包含 <algorithm>
    std::reverse(reversedStr.begin(), reversedStr.end()); // 使用标准库算法反转字符串
    return reversedStr;
}
int main()
{
    int num;
    cin >> num;
    if (num < 100 || num >= 1000) // 范围检查
        return -1;

    // 使用反转字符串的方法判断回文数
    string strNum = to_string(num);
    string reversedStr = reverseString(strNum);             // reverse
    reversedStr = reverseStringRangeBased(strNum); // range
    reversedStr = reverseStringByPointer(&strNum); // pointer 指针
    reversedStr = reverseStringBySTL(strNum);     // STL 标准模板库
    if (strNum == reversedStr)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}