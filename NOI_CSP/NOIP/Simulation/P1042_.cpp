#include <iostream>
#include <string>
using namespace std;

void Count(std::string &inputString, int mode)
{
    int player1 = 0, player2 = 0;
    for (char c : inputString)
    {
        if (c == 'E')
            break;
        player1 += c == 'W';    // 技巧1：借助逻辑值自动转换为 0 或 1 来简化判断
        player2 += c == 'L';
        if (max(player1, player2) >= mode)  // 技巧2：借助 max() 函数简化判断
        // if (player1 >= mode || player2 >= mode)
        {
            if (abs(player1 - player2) >= 2)  // 这里将判断条件拆为嵌套的 if，仅仅是为了代码可读性和便于添加上述注释
            {
                cout << player1 << ":" << player2 << endl;
                player1 = player2 = 0;
            }
        }
    }
    if (player1 > 0 || player2 > 0) // 如果去掉这一行，则遇到 'E' 直接退出时会输出 0:0
        cout << player1 << ":" << player2 << endl;
}

int main()
{
    string data, line;
    while (cin >> line)
    {
        data += line;
        // 行内找到 'E' 字符，结束输入
        if (line.find('E') != -1) // 不记得 string::npos 可以用 -1 代替，但不推荐
            break;
    }

    Count(data, 11);
    cout << endl;
    Count(data, 21);

    return 0;
}