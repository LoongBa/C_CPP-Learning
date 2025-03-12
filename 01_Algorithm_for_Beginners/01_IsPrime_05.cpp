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
    if (number < 2)
        return false;
    if (number == 2 || number == 3)
        return true; // 2 和 3 是素数
    // 第二次剪枝，直接排除偶数、3 的倍数。为何不排除 5、7、11 的倍数？
    if (number % 2 == 0 || number % 3 == 0)
        return false; // 排除 2 和 3 的倍数
    // 第一次剪枝，穷举范围减少一半，时间复杂度不变 O(n)
    int limit = number / 2;
    // 第三次剪枝，试除时排除偶数。
    // 第四次剪枝，试除时排除 6k-1/6k+1 的数。
    for (int i = 5; i < limit; i += 6)
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    return true;
}

int main()
{
    for (int i = 2; i <= 100; i++)
        if (isPrime(i))
            cout << i << " ";
}