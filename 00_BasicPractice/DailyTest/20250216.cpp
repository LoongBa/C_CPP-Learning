#include <iostream>
using namespace std;
int main()
{
    int id, group;
    cin >> id;
    if (id < 1 || id > 49) // 范围检查
        return -1;
    // 求学号的尾数(个位)
    int lastDigit = id % 10;
    // 对尾数求 3 的余数，作为组号
    group = lastDigit % 3 == 0 ? 3 : lastDigit % 3; // 利用三目运算符简化条件判断
    group = (lastDigit % 3) + 3 * (lastDigit % 3 == 0); // 利用逻辑值修正余数为 0 的情况
    group = (lastDigit + 2) % 3 + 1;    // 利用数学规律简化计算
    cout << group;
    return 0;
}