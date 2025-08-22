// P1303

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 将字符串转换为大整数
vector<int> stringToBigInt(string s)
{
    // 定义一个vector来存储大整数
    vector<int> a;
    // 从字符串的最后一个字符开始遍历
    for (int i = s.size() - 1; i >= 0; i--)
    {
        // 将字符转换为整数并添加到vector中
        a.push_back(s[i] - '0');
    }
    return a; // 返回大整数
}

// 将大整数转换为字符串
string bigIntToString(vector<int> a)
{
    string s;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        s += a[i] + '0';
    }
    return s;
}

// 去除大整数的前导零
vector<int> trimLeadingZeros(vector<int> &a){
    while(a.size() > 1 && a.back() == 0){
        a.pop_back();
    }
    return a;
}

// 大整数相乘
vector<int> multiply(vector<int> a, vector<int> b)
{
    vector<int> product = vector<int>(a.size() + b.size(), 0);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            product[i + j] += a[i] * b[j];
            product[i + j + 1] += product[i + j] / 10; // 处理进位
            product[i + j] %= 10;                      // 取余，仅保留余数
        }
    }
    return trimLeadingZeros(product); // 返回结果并去除前导零
}

// 大整数相加
vector<int> add(vector<int> a, vector<int> b)
{
    vector<int> sum = vector<int>(max(a.size(), b.size()), 0);
    int carry = 0; // 进位
    for (int i = 0; i < a.size() || i < b.size(); i++)
    {
        if (i < a.size()) // 如果a[i]存在，则加上a[i]
            sum[i] += a[i];
        if (i < b.size()) // 如果b[i]存在，则加上b[i]
            sum[i] += b[i];
        sum[i] += carry;     // 加上进位
        carry = sum[i] / 10; // 处理进位
        sum[i] %= 10;        // 取余，仅保留余数
    }
    if (carry) // 如果最后还有进位，则添加到结果中
        sum.push_back(carry);
    return sum;
}

// 大整数相减
vector<int> subtract(vector<int> a, vector<int> b)
{
    vector<int> difference = vector<int>(a.size(), 0);
    int borrow = 0; // 借位
    for (int i = 0; i < a.size(); i++)
    {
        difference[i] = a[i] - (i < b.size() ? b[i] : 0) - borrow; // 减去b[i]和借位
        if (difference[i] < 0)                                     // 如果结果小于0，则需要借位
        {
            difference[i] += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0; // 没有借位了
        }
    }
    // 去除前导零
    while (difference.size() > 1 && difference.back() == 0)
        difference.pop_back();
    return difference;
}

// 大整数相除（待完善）
vector<int> divide(vector<int> a, vector<int> b)
{
    vector<int> quotient = vector<int>(a.size(), 0);
    vector<int> remainder = a;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        remainder = add(remainder, remainder);
        if (remainder.size() > b.size())
        {
            remainder.pop_back(); // 如果余数大于除数，则去掉最高位
        }
    }
    return quotient; // 返回商（注意：此函数尚未完善）
}

int main()
{
    // 主函数内容待补充
}
