// https://www.luogu.com.cn/problem/P1141
// 为了教学需要，一步步对比：
// V0.0 : 基于递归的 dfs，没有缓存，每次都重新计算
// V1.0 : 基于递归的 dfs，但缓存了计算结果
// V2.0 : 基于 stack 模拟的 dfs
// V3.0 : 基于 bfs
// 当前版本为 V2.0
#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

// 用二维向量表示四个方向的变化量
vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 检查坐标是否有效
bool isValid(int n, int x, int y, int newX, int newY, const vector<vector<bool>> &visited, const vector<vector<char>> &maze)
{
    // 首先检查新坐标是否在迷宫范围内
    if (newX < 0 || newX >= n || newY < 0 || newY >= n)
        return false;

    // 检查新坐标对应的格子是否未被访问
    bool isNotVisited = !visited[newX][newY];

    // 检查新坐标对应的格子值与当前格子值是否不同
    bool isValueDifferent = maze[newX][newY] != maze[x][y];

    // 只有所有条件都满足，坐标才有效
    return isNotVisited && isValueDifferent;
}

// 基于栈的DFS函数
void dfs(int n, int startX, int startY, const vector<vector<char>> &maze, vector<vector<bool>> &visited, vector<pair<int, int>> &group)
{
    // 使用栈来模拟递归过程
    stack<pair<int, int>> tasks;

    // 标记当前位置为已访问，并加入连通块
    visited[startX][startY] = true;
    group.emplace_back(startX, startY);
    tasks.push({startX, startY}); // 压第一发子弹到弹匣

    // 当栈不为空时，继续搜索——清空弹匣：只要弹匣里有子弹，就一直射击
    while (!tasks.empty())
    {
        // 取出栈顶元素：取出弹匣顶部第一发子弹，压入枪膛
        int x = tasks.top().first;
        int y = tasks.top().second;
        tasks.pop(); // 射击

        // 遍历四个方向
        for (const auto &dir : directions)
        {
            int nextX = x + dir.first;
            int nextY = y + dir.second;
            // 检查新坐标是否有效，如果有效则入栈
            if (isValid(n, x, y, nextX, nextY, visited, maze))
            {
                // 标记当前位置为已访问，并加入连通块
                visited[nextX][nextY] = true;
                group.push_back({nextX, nextY});
                tasks.push({nextX, nextY}); // 压子弹到弹匣，用栈代替递归
            }
        }
    }
}

int main()
{
    // 加速输入输出，对于大数据量输入输出很重要
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> maze(n, vector<char>(n));
    vector<vector<int>> area(n, vector<int>(n, -1));         // 记录每一个位置的连通数
    vector<vector<bool>> visited(n, vector<bool>(n, false)); // 为当前连通块创建独立的访问标记数组

    // 读取迷宫数据
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < n; j++)
            maze[i][j] = str[j];
    }

    // 处理查询
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        // 输出查询位置的连通块大小（注意坐标从1开始，需要减1）
        if (area[--x][--y] == -1)
        {
            vector<pair<int, int>> group; // 存储当前连通块的所有位置

            // 从当前位置开始DFS搜索
            dfs(n, x, y, maze, visited, group);

            // 计算连通块大小
            int size = group.size();

            // 将连通块大小记录到area数组中
            for (const auto &pos : group)
                area[pos.first][pos.second] = size;
        }
        cout << area[x][y] << endl;
    }

    return 0;
}
