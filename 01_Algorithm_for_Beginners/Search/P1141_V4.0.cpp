// https://www.luogu.com.cn/problem/P1141
// 当前版本为 V4.0：使用并查集优化
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

// 用二维向量表示四个方向的变化量
vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 并查集数据结构
class UnionFind
{
private:
    vector<int> parent;
    vector<int> size;

public:
    UnionFind(int n)
    {
        parent.resize(n * n);
        size.resize(n * n, 1);
        for (int i = 0; i < n * n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (size[rootX] > size[rootY])
            {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
            else
            {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            }
        }
    }

    int getSize(int x)
    {
        return size[find(x)];
    }
};

// 检查坐标是否有效
bool isValid(int n, int x, int y, int newX, int newY, const vector<vector<char>> &maze)
{
    if (newX < 0 || newX >= n || newY < 0 || newY >= n)
        return false;
    return maze[newX][newY] != maze[x][y];
}

// 基于队列的BFS函数
void bfs(int n, int startX, int startY, const vector<vector<char>> &maze, vector<vector<bool>> &visited, UnionFind &uf)
{
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    int startIndex = startX * n + startY;
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (const auto &dir : directions)
        {
            int nextX = x + dir.first;
            int nextY = y + dir.second;
            if (isValid(n, x, y, nextX, nextY, maze) && !visited[nextX][nextY])
            {
                int currentIndex = x * n + y;
                int nextIndex = nextX * n + nextY;
                uf.unionSet(currentIndex, nextIndex);
                q.push({nextX, nextY});
                visited[nextX][nextY] = true;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> maze(n, vector<char>(n));
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    UnionFind uf(n);

    // 读取迷宫数据
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < n; j++)
        {
            maze[i][j] = str[j];
        }
    }

    // 预处理所有连通区域
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!visited[i][j])
            {
                bfs(n, i, j, maze, visited, uf);
            }
        }
    }

    // 处理查询
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        int index = x * n + y;
        cout << uf.getSize(index) << endl;
    }

    return 0;
}