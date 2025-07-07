#include <iostream>
#include <string>
using namespace std;

bool isNumber(char c)
{
    return c >= '0' && c <= '9';
}
bool isLower(char c)
{
    return c >= 'a' && c <= 'z';
}
char toUpper(char c)
{
    return c - 'a' + 'A';
}
string expendString(char left, char right, int p1, int p2, int p3)
{
    string extString;                      // 扩展后的字符串
    for (int i = left + 1; i < right; i++) // 构造字符的值：从 left + 1 到 right - 1
    {
        // 1. 准备扩展的字符，如果 p1 == 3，则扩展为星号，否则扩展为小写字母
        char c = i;
        if (p1 == 3)
            c = '*';
        else if (p1 == 2 && isLower(c)) // 数字 不做转换
            c = toUpper(c);             // 转换为大写
                                        // 2. 根据重复次数处理
        string repeatString;            // 重复的字符串
        for (int j = 0; j < p2; j++)
            repeatString += c;
        // if (p1 == 3) repeatString = "*"; // 题目歧义："*" 是否重复？——需要根据提交情况验证
        //  3. 处理顺序、逆序
        if (p3 == 1) // 如果 p3 == 1，则将 repeat 放在 extString 的末尾
            extString += repeatString;
        if (p3 == 2) // 如果 p3 == 2，则将 repeat 放在 extString 的开头
            extString = repeatString + extString;
    }
    return extString;
}
int main()
{
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    string line, result;
    cin >> line; // 如果使用 getline 就会被判定错误，除非使用：cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略到换行符为止的所有字符
    // cin.ignore();    // 忽略换行符
    // getline(cin, line);

    for (int i = 0; i < line.length(); i++)
    {
        char left = line[i]; // 当前字符
        result += left;      // 先添加当前字符

        // 仅当后续至少有2个字符时，才检查减号和右侧字符
        if (i < line.length() - 2)
        {
            char dash = line[i + 1];  // 下一个字符（可能为减号）
            char right = line[i + 2]; // 下下个字符

            if (dash == '-') // 若下一个字符是减号
            {
                // 检查是否满足展开条件：都是数字或都是小写字母
                bool sameType = (isNumber(left) && isNumber(right)) || (isLower(left) && isLower(right));
                if (right > left && sameType) // 检查 right 是否大于 left，且两者类型相同
                {
                    // 满足条件：展开并跳过减号和右侧字符
                    string ext = expendString(left, right, p1, p2, p3);
                    result += ext; // 扩展结果忽略减号（如果两个字符连续，返回 "" 也没有减号）
                    i += 1; // 仅跳过减号
                    continue;
                }
            }
        }
    }

    cout << result << endl;
    return 0;
}