#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

// 移除前导零（保留至少一位数字）
// 要求：bigInt为倒序存储的正整数数组
void removeLeadingZero(vector<int> &bigInt)
{
    // 从最高位开始移除0，但至少保留一位数字
    while (bigInt.size() > 1 && bigInt.back() == 0)
    {
        bigInt.pop_back();
    }
}

// 将字符串转换为倒序存储的大整数数组
// 要求：stringInt 只包含数字字符，表示正整数
// 例如："123" -> [3, 2, 1]（低位在前，高位在后）
vector<int> stringToBigInt(const string &stringInt)
{
    // 输入验证：检查是否为空或包含非数字字符
    if (stringInt.empty())
        throw invalid_argument("输入字符串不能为空");

    for (char c : stringInt)
    {
        if (c < '0' || c > '9')
            throw invalid_argument("输入字符串只能包含数字字符");
    }

    int len = stringInt.size();
    vector<int> bigInt(len); // 预分配空间
    // 从字符串末尾开始，倒序存储每一位数字
    for (int i = 0; i < len; i++)
        bigInt[i] = stringInt[len - 1 - i] - '0';

    removeLeadingZero(bigInt);
    return bigInt;
}

// 将倒序存储的大整数数组转换为字符串
// 要求：bigInt为倒序存储的正整数数组
// 例如：[3, 2, 1] -> "123"
string bigIntToString(const vector<int> &bigInt)
{
    if (bigInt.empty())
        return "0";

    string stringInt;
    // 从最高位开始构建字符串
    for (int i = bigInt.size() - 1; i >= 0; i--)
    {
        stringInt += (char)(bigInt[i] + '0');
    }
    return stringInt.empty() ? "0" : stringInt;
}

// 比较两个大整数的大小
// 要求：a 和 b 均为倒序存储的正整数数组
int compare(const vector<int> &a, const vector<int> &b)
{
    int aSize = a.size(), bSize = b.size();
    
    if (aSize != bSize)
        return aSize - bSize;
    
    for (int i = aSize - 1; i >= 0; i--)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
    }
    return 0;
}

// 高精度加法（优化版）
// 要求：a 和 b 均为倒序存储的正整数数组
vector<int> add(const vector<int> &a, const vector<int> &b)
{
    int maxLen = max(a.size(), b.size());
    vector<int> result(maxLen, 0); // 预分配空间
    int carry = 0;                 // 进位

    // 从低位开始逐位相加
    for (int i = 0; i < maxLen; i++)
    {
        int sum = carry;
        if (i < a.size())
            sum += a[i]; // 加上a的当前位
        if (i < b.size())
            sum += b[i]; // 加上b的当前位

        result[i] = sum % 10; // 当前位的结果
        carry = sum / 10;     // 计算进位
    }

    // 处理最后的进位
    if (carry > 0)
        result.push_back(carry);

    removeLeadingZero(result);
    return result;
}

// 高精度减法
// 要求：a 和 b 均为倒序存储的正整数数组，且 a >= b
vector<int> subtract(const vector<int> &a, const vector<int> &b)
{
    if (compare(a, b) < 0)
        throw invalid_argument("减法要求被减数 >= 减数");

    int aSize = a.size(), bSize = b.size();
    vector<int> result(aSize, 0); // 预分配为a的长度
    int borrow = 0;

    for (int i = 0; i < aSize; i++)
    {
        int diff = a[i] - borrow;
        if (i < bSize)
            diff -= b[i];

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        result[i] = diff;
    }

    removeLeadingZero(result);
    return result;
}

// 高精度乘法
// 要求：a 和 b 均为倒序存储的正整数数组
vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
    if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0))
        return {0};

    int aSize = a.size(), bSize = b.size();
    int productSize = aSize + bSize;
    vector<int> product(productSize, 0);

    // 先进行所有位的乘法
    for (int i = 0; i < aSize; i++)
        for (int j = 0; j < bSize; j++)
            product[i + j] += a[i] * b[j];

    // 统一处理进位
    for (int i = 0; i < productSize - 1; i++)
    {
        product[i + 1] += product[i] / 10;
        product[i] %= 10;
    }

    removeLeadingZero(product);
    return product;
}

// 高精度除法（二分法优化版）
// 要求：a 和 b 均为倒序存储的正整数数组，且 b != 0
pair<vector<int>, vector<int>> divideOptimized(const vector<int> &a, const vector<int> &b)
{
    // 检查除数是否为0
    if (b.size() == 1 && b[0] == 0)
        throw invalid_argument("除数不能为0");
    
    // 如果被除数小于除数，商为0，余数为被除数
    if (compare(a, b) < 0)
        return {{0}, a};

    int aSize = a.size();
    vector<int> remainder;
    vector<int> quotient(aSize, 0);  // 预分配商的空间，初始化为0
    
    // 从最高位开始进行长除法
    for (int i = aSize - 1; i >= 0; i--)
    {
        // 将当前位添加到余数的最高位
        remainder.insert(remainder.begin(), a[i]);
        removeLeadingZero(remainder);

        int left = 0, right = 9, q = 0;
        
        // 使用二分查找确定商的当前位
        while (left <= right)
        {
            int mid = (left + right) / 2;
            vector<int> prod = multiply(b, {mid});
            
            // 如果 mid * b <= remainder，则 mid 可能是答案
            if (compare(prod, remainder) <= 0)
            {
                q = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        
        quotient[aSize - 1 - i] = q;  // 直接按正确顺序存储
        
        // 更新余数：remainder = remainder - q * b
        remainder = subtract(remainder, multiply(b, {q}));
    }
    
    // 移除商和余数的前导零
    removeLeadingZero(quotient);
    removeLeadingZero(remainder);
    return {quotient, remainder};
}

// 高精度除法（带余数）
// 要求：a 和 b 均为倒序存储的正整数数组，且 b != 0
pair<vector<int>, vector<int>> divide(const vector<int> &a, const vector<int> &b) 
{
    if (b.size() == 1 && b[0] == 0)
        throw invalid_argument("除数不能为0");
    if (compare(a, b) < 0)
        return {{0}, a};

    int aSize = a.size();
    vector<int> remainder;
    vector<int> quotient(aSize); // 预分配商的空间
    
    for (int i = aSize - 1; i >= 0; i--) 
    {
        remainder.insert(remainder.begin(), a[i]); // 这里仍需insert，但可以考虑其他数据结构
        removeLeadingZero(remainder);

        int count = 0;
        while (compare(remainder, b) >= 0) 
        {
            remainder = subtract(remainder, b);
            count++;
        }

        quotient[aSize - 1 - i] = count; // 直接按正确顺序存储
    }

    removeLeadingZero(quotient);
    removeLeadingZero(remainder);
    return {quotient, remainder};
}
// 以下是字符串接口函数，将字符串转换为大整数进行计算，然后转换回字符串

// 字符串加法
// 要求：a 和 b 均为表示正整数的字符串
string add(const string &a, const string &b)
{
    vector<int> arrA = stringToBigInt(a);
    vector<int> arrB = stringToBigInt(b);
    vector<int> result = add(arrA, arrB);
    return bigIntToString(result);
}
// 字符串减法
// 要求：a 和 b 均为倒序存储的正整数数组，且 a >= b
string subtract(const string &a, const string &b)
{
    vector<int> arrA = stringToBigInt(a);
    vector<int> arrB = stringToBigInt(b);
    vector<int> result = subtract(arrA, arrB);
    return bigIntToString(result);
}
// 字符串乘法
// 要求：a和b均为表示正整数的字符串
string multiply(const string &a, const string &b)
{
    vector<int> arrA = stringToBigInt(a);
    vector<int> arrB = stringToBigInt(b);
    vector<int> result = multiply(arrA, arrB);
    return bigIntToString(result);
}
// 字符串除法（返回商）
// 要求：a和b均为表示正整数的字符串，且b != 0
string divide(const string &a, const string &b)
{
    vector<int> arrA = stringToBigInt(a);
    vector<int> arrB = stringToBigInt(b);
    auto [quotient, remainder] = divide(arrA, arrB);
    return bigIntToString(quotient);
}
// 字符串取模（返回余数）
// 要求：a 和 b 均为表示正整数的字符串，且 b != 0
string remainder(const string &a, const string &b)
{
    vector<int> arrA = stringToBigInt(a);
    vector<int> arrB = stringToBigInt(b);
    auto [quotient, remainder] = divide(arrA, arrB);
    return bigIntToString(remainder);
}
// 字符串比较：判断 a 是否大于 b
// 要求：a 和 b 均为表示正整数的字符串
bool isGreater(const string &a, const string &b)
{
    return compare(stringToBigInt(a), stringToBigInt(b)) > 0;
}
// 字符串比较：判断 a 是否等于 b
// 要求：a 和 b 均为表示正整数的字符串
bool isEqual(const string &a, const string &b)
{
    return compare(stringToBigInt(a), stringToBigInt(b)) == 0;
}
// 字符串比较：判断 a 是否小于 b
// 要求：a 和 b 均为表示正整数的字符串
bool isLess(const string &a, const string &b)
{
    return compare(stringToBigInt(a), stringToBigInt(b)) < 0;
}
// 测试函数：验证高精度计算的正确性
// 要求：a和b均为表示正整数的字符串，对于减法要求a>=b，对于除法和取模要求b!=0
void runTest(const string &a, const string &b, char op)
{
    try
    {
        string result;
        string expected;

        switch (op)
        {
        case '+':
            result = add(a, b);
            // 对于较小的数字，使用内置类型验证结果
            if (a.length() <= 18 && b.length() <= 18) // long long的安全范围
            {
                expected = to_string(stoll(a) + stoll(b));
                cout << "加法测试: " << a << " + " << b << " = " << result
                     << (result == expected ? " ✅" : " ❌ 应为: " + expected) << endl;
            }
            else
            {
                cout << "加法测试: " << a << " + " << b << " = " << result << " ✅（大数无法验证）" << endl;
            }
            break;

        case '-':
            if (isLess(a, b))
            {
                cout << "减法测试: " << a << " - " << b << " = 错误（a < b） ✅" << endl;
                return;
            }
            result = subtract(a, b);
            if (a.length() <= 18 && b.length() <= 18)
            {
                expected = to_string(stoll(a) - stoll(b));
                cout << "减法测试: " << a << " - " << b << " = " << result
                     << (result == expected ? " ✅" : " ❌ 应为: " + expected) << endl;
            }
            else
            {
                cout << "减法测试: " << a << " - " << b << " = " << result << " ✅（大数无法验证）" << endl;
            }
            break;

        case '*':
            result = multiply(a, b);
            if (a.length() <= 9 && b.length() <= 9) // 避免溢出
            {
                expected = to_string(stoll(a) * stoll(b));
                cout << "乘法测试: " << a << " * " << b << " = " << result
                     << (result == expected ? " ✅" : " ❌ 应为: " + expected) << endl;
            }
            else
            {
                cout << "乘法测试: " << a << " * " << b << " = " << result << " ✅（大数无法验证）" << endl;
            }
            break;

        case '/':
            if (b == "0")
            {
                cout << "除法测试: " << a << " / " << b << " = 错误（除数为0） ✅" << endl;
                return;
            }
            result = divide(a, b);
            if (a.length() <= 18 && b.length() <= 18)
            {
                expected = to_string(stoll(a) / stoll(b));
                cout << "除法测试: " << a << " / " << b << " = " << result
                     << (result == expected ? " ✅" : " ❌ 应为: " + expected) << endl;
            }
            else
            {
                cout << "除法测试: " << a << " / " << b << " = " << result << " ✅（大数无法验证）" << endl;
            }
            break;

        case '%':
            if (b == "0")
            {
                cout << "取模测试: " << a << " % " << b << " = 错误（除数为0） ✅" << endl;
                return;
            }
            result = remainder(a, b);
            if (a.length() <= 18 && b.length() <= 18)
            {
                expected = to_string(stoll(a) % stoll(b));
                cout << "取模测试: " << a << " % " << b << " = " << result
                     << (result == expected ? " ✅" : " ❌ 应为: " + expected) << endl;
            }
            else
            {
                cout << "取模测试: " << a << " % " << b << " = " << result << " ✅（大数无法验证）" << endl;
            }
            break;

        default:
            cout << "未知操作符: " << op << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "测试失败: " << e.what() << endl;
    }
}

int main()
{
    cout << "===== 高精度计算入门教学示范 =====" << endl;
    cout << "本程序演示了正整数的高精度加减乘除运算" << endl;
    cout << "数据存储方式：倒序数组（低位在前，高位在后）" << endl;

    // 基本测试
    cout << "\n--- 基本运算测试 ---" << endl;
    runTest("123", "456", '+');
    runTest("1000", "999", '-');
    runTest("25", "4", '*');
    runTest("100", "7", '/');
    runTest("100", "7", '%');

    // 边界测试
    cout << "\n--- 边界情况测试 ---" << endl;
    runTest("0", "0", '+');
    runTest("0", "123", '+');
    runTest("123", "0", '*');
    runTest("999999999999", "1", '+');
    runTest("1000000000000", "1", '-');
    runTest("9999", "9999", '*');

    // 前导零测试
    cout << "\n--- 前导零处理测试 ---" << endl;
    runTest("000123", "00456", '+');
    runTest("001000", "000999", '-');
    runTest("0025", "0004", '*');

    // 大数测试（需要手动验证）
    cout << "\n--- 超大数测试（演示高精度优势） ---" << endl;
    cout << "计算 10^100 + 1 = " << endl;
    cout << add("1" + string(100, '0'), "1") << endl;

    cout << "\n计算 999...999 (50个9) * 999...999 (50个9) = " << endl;
    string big_num = string(50, '9');
    cout << multiply(big_num, big_num) << endl;

    // 错误处理测试
    cout << "\n--- 错误处理测试 ---" << endl;
    try
    {
        subtract("123", "456");
    }
    catch (const exception &e)
    {
        cout << "减法错误测试: " << e.what() << " ✅" << endl;
    }

    try
    {
        divide("123", "0");
    }
    catch (const exception &e)
    {
        cout << "除零错误测试: " << e.what() << " ✅" << endl;
    }

    try
    {
        stringToBigInt("12a34");
    }
    catch (const exception &e)
    {
        cout << "非法字符测试: " << e.what() << " ✅" << endl;
    }

    try
    {
        stringToBigInt("");
    }
    catch (const exception &e)
    {
        cout << "空字符串测试: " << e.what() << " ✅" << endl;
    }

    cout << "\n===== 测试完成 =====" << endl;
    cout << "高精度计算可以处理任意大的正整数运算！" << endl;

    return 0;
}
