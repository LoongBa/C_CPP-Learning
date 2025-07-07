// 05-21-D01-字符串逆序(2)(L4)
// 输入数据第一行为一个正整数n，n≤100。接下来有n行，每行为一个字符串，字符串中可能会包含空格，长度不超过100个字符。
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    cin >> n;
    cin.ignore();
    
    for (int i = 0; i < n; i++)
    {
        string line, out;
        getline(cin, line);
        for (char c : line)
        {
            out = c + out;
        }
        cout << out << endl;
    }

    return 0;
}