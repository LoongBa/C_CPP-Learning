// https://www.luogu.com.cn/problem/P1141
// 为了教学需要，一步步对比：
// V0.0 : 基于递归的 dfs，没有缓存，每次都重新计算
// V1.0 : 基于递归的 dfs，但缓存了计算结果
// V2.0 : 基于 stack 模拟的 dfs
// V3.0 : 基于 bfs
// 当前版本为 V3.2：配合邻接表，基于一维数组保存 visited 和 area
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

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
void bfs(int n, int startIndex, const vector<vector<int>> &adjList, vector<bool> &visited, vector<int> &group)
{
    // 使用队列来实现 BFS
    queue<int> tasks;

    // 标记当前位置为已访问，并加入连通块
    visited[startIndex] = true;
    group.push_back(startIndex);
    tasks.push(startIndex); // 压第一发子弹到弹链

    // 当队列不为空时，继续搜索
    while (!tasks.empty())
    {
        // 取出队列前部元素：取出弹链前部第一发子弹，压入枪膛
        int currentIndex = tasks.front();
        tasks.pop();

        // 遍历当前索引的所有邻接边——开始加入邻接边时，已经向四个方向扩展过
        for (int nextIndex : adjList[currentIndex])
        {
            // 新坐标没有访问过则加入队列——开始加入邻接边时，已经检查过是否有效
            if (!visited[nextIndex])
            {
                // 标记当前位置为已访问，并加入连通块
                visited[nextIndex] = true;
                group.push_back(nextIndex);
                tasks.push(nextIndex); // 压子弹到弹链
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
    vector<int> area(n * n, -1);        // 记录每一个位置的连通数，改为一维数组
    vector<bool> visited(n * n, false); // 为当前连通块创建独立的访问标记数组，改为一维数组
    vector<vector<int>> adjList(n * n); // 定义邻接表

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
                if (canGo(n, i, j, nextX, nextY, maze))
                {
                    int edgeIndex = toIndex(n, nextX, nextY);
                    adjList[index].push_back(edgeIndex); // 将符合条件的边，加入邻接表
                }
            }
        }
    }

    // 处理查询
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        // 转换为0-based索引
        x--;
        y--;
        int index = toIndex(n, x, y);

        // 如果该位置还未计算过连通块大小
        if (area[index] == -1)
        {
            vector<int> group; // 存储当前连通块的所有位置索引

            // 从当前位置开始BFS搜索
            bfs(n, index, adjList, visited, group);

            // 计算连通块大小
            int size = group.size();

            // 将连通块大小记录到area数组中
            for (int idx : group)
                area[idx] = size;
        }
        cout << area[index] << endl;
    }

    return 0;
}
