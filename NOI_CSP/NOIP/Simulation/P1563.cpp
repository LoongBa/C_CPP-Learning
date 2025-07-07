#include <iostream>
#include <string>
#include <vector>
using namespace std;

// NOIP 2016 提高组：玩具小人[P1563]
int main()
{
    // 读取数量
    int n, m;
    cin >> n >> m;

    // 读取方向和名字
    vector<int> directions(n);
    vector<string> names(n);
    for (int i = 0; i < n; ++i)
        cin >> directions[i] >> names[i];

    // 读取指令
    vector<int> commands(m);
    vector<int> steps(m);
    for (int i = 0; i < m; ++i)
        cin >> commands[i] >> steps[i];

    // 开始计算
    int position = 0; // 初始位置为第1个玩具小人
    for (int i = 0; i < m; ++i)
    {
        int command = commands[i];      // 指令方向：0=左数，1=右数
        int s = steps[i];               // 步长
        int dir = directions[position]; // 当前位置的玩具小人朝向
        
        // 根据朝向和指令方向计算实际移动方向
        int step = 0;
        if (dir == 0) { // 朝内：左数顺时针(-s)，右数逆时针(+s)
            step = (command == 0) ? -s : s;
        } else { // 朝外：左数逆时针(+s)，右数顺时针(-s)
            step = (command == 0) ? s : -s;
        }
        
        // 更新位置：约瑟夫环问题——取模
        position = (position + step + n) % n;   //技巧：加 n 再取模，防止负数取模
    }

    // 输出最终位置的玩具小人名字
    cout << names[position] << endl;
    return 0;
}