/*
求 100 之内的素数（质数）
- 写一个函数 `isPrime(number:int)` 判断 `number` 是否是素数，如果是则返回 `True`，否则返回 `False`；
- 然后用 `1-100` 的循环调用这个函数，判断每一个数字是否是素数并输出，如：
> 素数：2, 3, 5, 7, 11, ....
> 非素数：1, 4, 6, 8, 9, 10, ...
*/
// 试除法判断素数
#include <iostream>
using namespace std;

// 判断一个数是否是素数：试除法
bool isPrime(int number)
{
    if (number < 2) return false;
    // 试除法：第一次剪枝，穷举范围减少一半，时间复杂度不变 O(n)
    int limit = number / 2;
    for (int i = 2; i < limit; i++)
        if (number % i == 0)
            return false;
    return true;
}

int main()
{
    for (int i = 2; i <= 100; i++)
        if (isPrime(i))
            cout << i << " ";
}