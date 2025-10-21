// https://www.luogu.com.cn/problem/P1141
// 为了教学需要，一步步对比：
// V0.0 : 基于递归的 dfs，没有缓存，每次都重新计算
// V1.0 : 基于递归的 dfs，但缓存了计算结果
// V2.0 : 基于 stack 模拟的 dfs
// V3.0 : 基于 bfs（教学优化版：复用队列+清晰逻辑）
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 四个方向：上、右、下、左（像游戏中的方向键）
vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main()
{
    // 加速输入输出，大数据量时非常重要
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m; // n: 迷宫大小，m: 查询次数

    // 存储迷宫数据（0或1表示不同颜色）
    vector<vector<char>> maze(n, vector<char>(n));
    // area数组三重复用：
    // -1: 未访问过该格子
    // 0: 已访问但未计算连通块大小
    // >0: 已计算的连通块大小（最终结果）
    vector<vector<int>> area(n, vector<int>(n, -1));

    // 读取迷宫数据
    for (int i = 0; i < n; ++i)
    {
        string row;
        cin >> row;
        for (int j = 0; j < n; ++j)
        {
            maze[i][j] = row[j];
        }
    }

    // 处理每个查询
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        x--; // 转换为0开始的坐标（题目输入是1开始）
        y--;

        // 情况1：已经计算过这个格子的连通块大小，直接输出
        if (area[x][y] != -1)
        {
            cout << area[x][y] << '\n';
            continue;
        }

        // 情况2：第一次查询，需要BFS计算连通块大小
        queue<pair<int, int>> q; // 复用队列：先用于计算大小，再用于回填结果

        // 初始化起点：标记为"已访问但未计算"，加入队列
        area[x][y] = 0;
        q.emplace(x, y);

        int size = 0; // 记录连通块的大小

        // 第一阶段BFS：计算连通块大小
        while (!q.empty())
        {
            // 取出队头格子（当前要处理的格子）
            auto [cx, cy] = q.front();
            q.pop();
            size++; // 计数+1

            // 检查四个方向的邻居
            for (auto [dx, dy] : directions)
            {
                int nx = cx + dx; // 邻居x坐标
                int ny = cy + dy; // 邻居y坐标

                // 短路判断：依次检查"是否出界→颜色是否不同→是否未访问"
                if (nx < 0 || nx >= n)
                    continue; // 出界：跳过
                if (ny < 0 || ny >= n)
                    continue; // 出界：跳过
                if (maze[nx][ny] == maze[cx][cy])
                    continue; // 颜色相同：跳过
                if (area[nx][ny] != -1)
                    continue; // 已访问：跳过

                // 符合条件的邻居：标记为"已访问但未计算"，加入队列
                area[nx][ny] = 0;
                q.emplace(nx, ny);
            }
        }

        // 第二阶段BFS：回填连通块大小（复用同一个队列）
        q.emplace(x, y);   // 从起点重新开始
        area[x][y] = size; // 起点先标记

        while (!q.empty())
        {
            auto [cx, cy] = q.front();
            q.pop();

            // 检查四个方向的邻居
            for (auto [dx, dy] : directions)
            {
                int nx = cx + dx;
                int ny = cy + dy;

                // 短路判断：依次检查"是否出界→颜色是否不同→是否待回填"
                if (nx < 0 || nx >= n)
                    continue;
                if (ny < 0 || ny >= n)
                    continue;
                if (maze[nx][ny] == maze[cx][cy])
                    continue;
                if (area[nx][ny] != 0)
                    continue; // 不是待回填状态：跳过

                // 符合条件的邻居：回填大小，加入队列继续处理
                area[nx][ny] = size;
                q.emplace(nx, ny);
            }
        }

        // 输出当前查询的结果
        cout << size << "\n";
    }

    return 0;
}
