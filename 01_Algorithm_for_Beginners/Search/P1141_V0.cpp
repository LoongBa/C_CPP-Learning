// https://www.luogu.com.cn/problem/P1141
// 为了教学需要，一步步对比：
// V0.0 : 基于递归的 dfs，没有缓存，每次都重新计算
// V1.0 : 基于递归的 dfs，但缓存了计算结果
// V2.0 : 基于 stack 模拟的 dfs
// V3.0 : 基于 bfs
// 当前版本为 V0.0
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// 用二维向量表示四个方向的变化量
vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 检查坐标是否有效
// 参数说明：
//   n - 迷宫大小
//   x, y - 当前坐标
//   newX, newY - 要检查的新坐标
//   visited - 访问标记数组
//   maze - 迷宫数据
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

// DFS 函数
// 参数说明：
//   n - 迷宫大小
//   x, y - 当前坐标
//   maze - 迷宫数据
//   visited - 访问标记数组
//   path - 当前连通块的路径
void dfs(int n, int x, int y, const vector<vector<char>> &maze, vector<vector<bool>> &visited, vector<pair<int, int>> &path)
{
    // 如果当前位置已被访问，则返回
    if (visited[x][y])
        return;

    // 标记当前位置为已访问，并加入连通块路径
    visited[x][y] = true;
    path.emplace_back(x, y);

    // 遍历四个方向
    for (const auto &dir : directions)
    {
        int nextX = x + dir.first;
        int nextY = y + dir.second;

        // 检查新坐标是否有效，如果有效则递归搜索
        if (isValid(n, x, y, nextX, nextY, visited, maze))
            dfs(n, nextX, nextY, maze, visited, path);
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

    // 读取迷宫数据
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < n; j++)
            maze[i][j] = str[j];
    }

    // 处理查询，每次查询都重新计算连通块大小
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--; // 转换为0-based索引

        // 为每次查询创建新的访问标记数组和路径
        vector<pair<int, int>> path;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        // 从查询位置开始DFS搜索
        dfs(n, x, y, maze, visited, path);

        // 输出连通块大小
        cout << path.size() << endl;
    }

    return 0;
}
