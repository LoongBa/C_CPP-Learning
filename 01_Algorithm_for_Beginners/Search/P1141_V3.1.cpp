// https://www.luogu.com.cn/problem/P1141
// 为了教学需要，一步步对比：
// V0.0 : 基于递归的 dfs，没有缓存，每次都重新计算
// V1.0 : 基于递归的 dfs，但缓存了计算结果
// V2.0 : 基于 stack 模拟的 dfs
// V3.0 : 基于 bfs
// 当前版本为 V3.1，将 visited 数组改为多次搜索共享，避免重复创建和初始化
#include <iostream>
#include <vector>
#include <utility>
#include <queue> // 改用queue头文件

using namespace std;

// 用二维向量表示四个方向的变化量
vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 坐标转索引
int toIndex(int n, int x, int y)
{
    return x * n + y;
}
// 索引转坐标
pair<int, int> toCoord(int n, int index)
{
    return {index / n, index % n};
}

// 检查坐标是否有效
bool canGo(int n, int x, int y, int newX, int newY, const vector<vector<char>> &maze)
{
    // 首先检查新坐标是否在迷宫范围内
    if (newX < 0 || newX >= n || newY < 0 || newY >= n)
        return false;

    // 检查新坐标对应的格子值与当前格子值是否不同
    bool isValueDifferent = maze[newX][newY] != maze[x][y];

    // 只有所有条件都满足，坐标才有效
    return isValueDifferent;
}

// 基于队列的BFS函数
void bfs(int n, int startX, int startY, const vector<vector<int>> &adjList, vector<vector<bool>> &visited, vector<pair<int, int>> &group)
{
    // 使用队列来实现 BFS
    queue<pair<int, int>> tasks;

    // 标记当前位置为已访问，并加入连通块
    visited[startX][startY] = true;
    group.push_back({startX, startY});
    tasks.push({startX, startY}); // 压第一发子弹到弹链

    // 当队列不为空时，继续搜索——清空弹链：只要弹链里有子弹，就一直射击
    while (!tasks.empty())
    {
        // 取出队列前部元素：取出弹链前部第一发子弹，压入枪膛
        int x = tasks.front().first;
        int y = tasks.front().second;
        tasks.pop(); // 射击

        // 遍历当前坐标的所有邻接边——开始加入邻接边时，已经向四个方向扩展过
        int index = toIndex(n, x, y);
        for (int edgeIndex : adjList[index])
        {
            // 计算邻接边的坐标
            auto nextPos = toCoord(n, edgeIndex);
            // 新坐标没有访问过则加入队列——开始加入邻接边时，已经检查过是否有效
            if (!visited[nextPos.first][nextPos.second])
            {
                // 标记当前位置为已访问，并加入连通块
                visited[nextPos.first][nextPos.second] = true;
                group.push_back(nextPos);
                tasks.push(nextPos); // 压子弹到弹链
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
    vector<vector<int>> adjList(n * n);                      // 定义邻接表

    // 读取迷宫数据
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < n; j++)
            maze[i][j] = str[j];
    }
    // 构建邻接表
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int index = toIndex(n, i, j);
            for (auto direction : directions)
            {
                int nextX = i + direction.first;
                int nextY = j + direction.second;
                int edgeIndex = toIndex(n, nextX, nextY);
                if (canGo(n, i, j, nextX, nextY, maze))
                    adjList[index].push_back(edgeIndex); // 将符合条件的边，加入邻接表
            }
        }
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

            // 从当前位置开始BFS搜索
            bfs(n, x, y, adjList, visited, group);

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
