// P1255 数楼梯
// https://www.luogu.com.cn/problem/P1255
/*
通过动态规划的方法，根据楼梯阶数 n 计算不同的走法数量。
采用了一种混合策略，在数值较小时使用 long long 类型进行普通加法运算，当数值可能超出 long long 的表示范围时，切换到高精度加法运算（以字符串形式实现）。
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 高精度加法
string addStrings(string num1, string num2)
{
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    string result;
    int carry = 0;
    int i = 0;

    while (i < num1.size() || i < num2.size() || carry)
    {
        int digit1 = i < num1.size() ? num1[i] - '0' : 0;
        int digit2 = i < num2.size() ? num2[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
        i++;
    }

    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    int n;
    cin >> n;

    if (n <= 1)
    {
        cout << 1 << endl;
        return 0;
    }

    const long long threshold = 1e18; // 设置阈值
    long long prev_prev = 1;          // dp[0]
    long long prev = 1;               // dp[1]
    bool useHighPrecision = false;    // 标记是否使用高精度
    string str_prev_prev, str_prev;   // 高精度计算用的字符串

    for (int i = 2; i <= n; i++)
    {
        if (!useHighPrecision)
        {
            // 检查是否会溢出
            if (prev > threshold - prev_prev)
            {
                // 即将溢出，切换到高精度
                useHighPrecision = true;
                str_prev_prev = to_string(prev_prev);
                str_prev = to_string(prev);
                string current = addStrings(str_prev_prev, str_prev);
                str_prev_prev = str_prev;
                str_prev = current;
            }
            else
            {
                // 普通加法
                long long current = prev_prev + prev;
                prev_prev = prev;
                prev = current;
            }
        }
        else
        {
            // 高精度加法
            string current = addStrings(str_prev_prev, str_prev);
            str_prev_prev = str_prev;
            str_prev = current;
        }
    }

    if (useHighPrecision)
    {
        cout << str_prev << endl;
    }
    else
    {
        cout << prev << endl;
    }

    return 0;
}
