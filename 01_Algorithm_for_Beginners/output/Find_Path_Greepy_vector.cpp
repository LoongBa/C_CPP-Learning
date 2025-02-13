#include <cstdlib>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>    // C++ STL 标准模板库中的 vector 容器 STL: Standard Template Library
using namespace std; // std = standard 缩写

/************************************
    算法入门练习：贪心算法2
    熟悉 C++ 类：用 vector 代替数组
************************************/
/* 掌握词汇：
    typedef 类型定义: type 类型，define 定义
    struct 结构体，structure 结构
*/
struct Point
{
    int x;
    int y;
};

vector<Point> create_map(int n)
{
    srand(time(0));
    // 如果不指定长度，vector 容器是可变长度的，则使用 push_back() 方法添加元素
    // 初始化一个长度为 n 的 vector 容器
    vector<Point> map = vector<Point>(n); 
    // 因为指定了长度，实际上已经分配了 n 个 Point 元素长度的内存
    // 所以，下面可以用索引/下标访问元素
    for (int i = 0; i < n; i++)
    // 不能超出 vector 容器的长度，否则会出现【越界】错误
    // 如果超出了初始化时的长度，则使用 push_back()，vector 会自动扩容
    {
        map[i].x = rand() % 100;
        map[i].y = rand() % 100;
    }
    // 这里需要释放内存么？
    // 不能，因为需要返回给调用者，如果这里释放了内存，调用者就无法使用这个内存了
    // 另外，vector 容器会自动释放内存，不需要手动释放内存
    return map;
}

double distance(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
/**
 * @brief 使用贪心算法找到从起始点开始的路径
 *
 * 该函数通过贪心算法，从给定的起始点开始，每次选择距离当前点最近且未访问过的点，直到遍历完所有点。
 *
 * @param map 包含所有点的数组
 * @param map_length 点数组的长度
 * @param start 起始点
 * @return Point* 包含路径的点数组
 */
vector<Point> find_path_greepy(vector<Point> map, Point startPoint)
{
    int map_length = map.size(); // 获取 map 的长度
    // 用于存储路径
    vector<Point> path = vector<Point>(map_length);
    // 用于标记每个点是否被访问过
    //vector<int> visited = vector<int>(map_length);
    vector<bool> visited = vector<bool>(map_length); 
    // 遍历所有点
    for (int i = 0; i < map_length; i++)
    {
        // 初始化最小距离为一个较大的值
        double min_distance = 1000000000;
        // 初始化最小距离点的索引为 0
        int min_index = 0;
        // 初始化当前距离为 0
        double dis = 0;
        // 输出当前迭代的信息
        cout << "No." << i << " (" << startPoint.x << "," << startPoint.y << ")" << endl;
        // 遍历所有点
        for (int j = 0; j < map_length; j++)
        {
            // 如果该点已经被访问过，则跳过
            if (visited[j] == true)    // bool 类型，true 和 false
                continue;
            // cout << "\t" << map[j].x << "," << map[j].y << endl;
            //  获取当前点
            Point point = map[j];   // vector 支持用 下标/索引 访问元素
            // 计算当前点与起始点的距离
            dis = distance(point, startPoint);
            // 如果当前距离小于最小距离
            if (dis < min_distance)
            {
                // 更新最小距离
                min_distance = dis;
                // 更新最小距离点的索引
                min_index = j;
            }
            // 输出当前点的信息和距离
            cout << "\tNo." << j;
            cout << "\t" << "(" << startPoint.x << "," << startPoint.y << ")" << " to ";
            cout << "(" << point.x << "," << point.y << ")" << " dis:";
            cout << dis << " ? ";
            cout << min_distance << endl;
        }
        // 将最小距离的点加入路径
        path[i] = map[min_index];
        // 标记该点为已访问
        visited[min_index] = true; // bool 类型可以用 true 和 false 表示
        // 更新起始点为路径中的下一个点
        startPoint = path[i];
        // 输出选择的点的信息
        cout << "Choosed:" << "<" << min_index << "> " << "(" << startPoint.x << "," << startPoint.y << ")" << endl;
    }
    // 返回路径
    //delete[] visited; // 不需要释放内存，因为 vector 容器会自动释放内存
    return path;
}

int main()
{
    // 创建坐标地图
    int n = 10;
    vector<Point> map = create_map(n); // create 创造；generate
    // <> 是泛型的语法，表示模板参数，用于表示任意类型
    // vector<Point> 表示：【vector 容器】中存储的【元素类型】是 Point 结构体
    // vector<int>，或者 vector<char> = string

    // 用贪心算法计算最优路径
    int length = n;
    Point startPoint = Point{10, 13}; // 掌握定义 struct 结构体的方法
    vector<Point> path = find_path_greepy(map, startPoint);
    // 输出最优路径
    cout << "Greedy Algorithm: " << endl;
    cout << "Length: " << length << endl;
    cout << "Path: (" << startPoint.x << ", " << startPoint.y << ")";
    for (int i = 0; i < length; i++)
    {
        cout << " -> (" << path[i].x << ", " << path[i].y << ")";
    }

    // 不需要释放内存，因为 vector 容器会自动释放内存
    // delete[] map;  
    // map = nullptr; 
    // delete[] path; 
    // path = nullptr;

    return 0;
}
