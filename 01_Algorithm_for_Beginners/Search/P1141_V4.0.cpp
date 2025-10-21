#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// 方向数组
const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// 判断是否可以到达新位置
bool canGo(int n, int x, int y, int nextX, int nextY, const vector<vector<char>> &maze)
{
    // 必须先检查边界
    if (nextX < 0 || nextX >= n || nextY < 0 || nextY >= n)
    {
        return false;
    }
    // 检查是否可以移动：0只能移动到1，1只能移动到0
    return maze[x][y] != maze[nextX][nextY];
}

// 并查集初始化函数
void init(vector<int> &parent, vector<int> &size, int n)
{
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i; // 初始时每个节点都是自己的父节点
        size[i] = 1;   // 初始时每个连通块大小为1
    }
}

// 并查集查找函数（带路径压缩）
int find(vector<int> &parent, int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent, parent[x]); // 路径压缩
    }
    return parent[x];
}

// 并查集合并函数（按大小合并）
void unite(vector<int> &parent, vector<int> &size, int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY)
    {
        // 按大小合并：小的树合并到大的树下
        if (size[rootX] < size[rootY])
        {
            swap(rootX, rootY);
        }
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    }
}

int main()
{
    int n, m;
    cin >> n >> m; // 读入迷宫大小和查询次数

    vector<vector<char>> maze(n, vector<char>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> maze[i][j];
        }
    }

    // 初始化并查集
    int totalNodes = n * n;
    vector<int> parent(totalNodes);
    vector<int> size(totalNodes);
    init(parent, size, totalNodes);

    // 构建并查集
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int currentNode = i * n + j;
            // 检查四个方向
            for (const auto &dir : directions)
            {
                int nextX = i + dir.first;
                int nextY = j + dir.second;
                if (canGo(n, i, j, nextX, nextY, maze))
                {
                    int neighborNode = nextX * n + nextY;
                    unite(parent, size, currentNode, neighborNode);
                }
            }
        }
    }

    // 处理每个查询
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--; // 转换为0-based坐标
        int node = x * n + y;
        int root = find(parent, node);
        cout << size[root] << endl;
    }

    return 0;
}
