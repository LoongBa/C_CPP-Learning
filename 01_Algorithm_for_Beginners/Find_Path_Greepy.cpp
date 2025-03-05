#include <cstdlib>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
using namespace std;

/************************************
    算法入门练习：贪心算法
    熟悉 C/C++ 内存分配、初始化和释放
************************************/
/* 掌握词汇：
    typedef 类型定义: type 类型，define 定义
    struct 结构体，structure 结构
*/
typedef struct
{
    int x;
    int y;
} Point;

Point *create_map(int n)
{
    srand(time(0));
    Point *map = new Point[n];
    for (int i = 0; i < n; i++)
    {
        map[i].x = rand() % 100;
        map[i].y = rand() % 100;
    }
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
Point* find_path_greepy(Point map[], int map_length, Point start)
{
    // 分配内存用于存储路径
    Point *path = new Point[map_length];
    // 分配内存用于标记每个点是否被访问过
    int *visited = new int[map_length];
    // 初始化所有点为未访问状态
    fill(visited, visited + map_length, 0);     
    // 对比：void fill(int* first, int* last, int value); value 是填充的值
    // fill() 是 C++ 提供的方法，需要引用头文件 <cstdlib>
    // fill(指针, 指针 + 长度, 填充的值) —— 长度是指填充的次数而不是字节数
    // fill(visited, visited + map_length, 0) 就是将 visited 数组的前 map_length 个元素都设置为 0
    //
    // 对比：void* malloc(size_t size);
    // malloc() 是 C 语言提供的方法，需要引用头文件 <stdlib.h> 或 <cstdlib>
    // malloc 分配内存时，提供的长度是指字节数，而不是元素个数
    // 例如，malloc(10) 分配了 10 个字节的内存，而不是 10 个元素的内存
    // malloc(sizeof(int)*10) 分配了 10 个 int 类型的元素的内存——长度是 10 * 4 = 40 字节
    // ——使用 sizeof() 函数【避免硬编码】，比如 32位系统中 int 类型占 4 字节，64位系统中 int 类型占 8 字节，长度不同
    // calloc 分配内存时，提供的长度是指字节数，而不是元素个数
    //
    // 对比：void* calloc(size_t num, size_t size);
    // calloc(10, sizeof(int)) 分配了 10 个 int 类型的元素的内存——长度是 10 * 4 = 40 字节的内存，并将它们都初始化为 0
    // calloc() 分配内存时，会自动将内存初始化为 0，而 malloc() 分配内存时，不会自动初始化内存
    // calloc() 性能比 malloc() 慢，因为 calloc() 需要初始化内存，而 malloc() 不需要
    // 当需要更高的性能，以及不需要初始化内存，则使用 malloc()
    // 否则，可以使用 calloc() 或 new 分配内存，fill() 来初始化内存
    // C 使用 memset() 函数来初始化内存，memset() 函数需要引用头文件 <cstring> 或 <string.h>
    // memset(指针, 填充的值, 长度) —— 长度是指填充的【字节数】而不是元素个数，适合初始化字符串而非其它类型（尤其结构体等复杂类型）
    //
    // 小结：
    // 1. 当需要更高的性能，以及不需要初始化内存，则使用 malloc()。当需要初始化字符串，则使用 memset() 函数
    // 2. 性能要求没那么高时：使用 calloc() 分配并初始化内存为 0，
    // 3. 当性能要求没那么高时，还可以使用 C++ 的内存分配方式：new 分配内存，fill() 来初始化内存
    // 4.1 释放内存：使用 malloc()/calloc() 分配的内存，使用 free() 释放内存；
    // 4.2 使用 new 分配的内存，使用 delete 释放内存
    // 要求掌握： C++ 的内存分配、初始化、释放方式：new/delete，能写 C++ 代码；
    // 要求熟悉：C 的内存分配、初始化、释放方式：malloc/calloc/memset/free，能看懂用 C 写的代码
    
    // 定义类型和定义结构体
    /*  
    struct Point {
            int x; 
            int y;
        }; 
    Point point{1, 2};                      // 在 堆栈/stack 中分配内存，不需要手动释放内存
        //Point *point = new Point; 
        Point *point = new Point{1, 2};     // 在 堆/heap 中分配内存，需要手动释放内存
    delete *point; // 释放内存：在堆上分配的内存，如果不释放，将造成内存泄漏
    point = nullptr; // 释放内存后，将指针设置为 nullptr，避免出现野指针：指向已释放的内存的指针，错误的使用野指针可能导致程序崩溃或产生【不可预测的结果】
    在堆栈与堆中分配内存的区别：
    1. 堆栈：自动分配和释放内存，不需要手动释放内存，由编译器自动管理——代码运行时，一旦离开变量的【作用域】，会自动释放内存
    2. 堆：手动分配和释放内存，需要手动释放内存，否则会造成内存泄漏
    */


    // 将起始点添加到路径中
                                                
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
        cout << "No." << i << " (" << start.x << "," << start.y << ")"  << endl;
        // 遍历所有点
        for (int j = 0; j < map_length; j++)
        {
            // 如果该点已经被访问过，则跳过
            if (visited[j] == 1) continue;
            //cout << "\t" << map[j].x << "," << map[j].y << endl;
            // 获取当前点
            Point point = map[j];
            Point* pointPtr = &map[j]; // 使用 Point* 指针时，访问它的子对象需要用 -> 箭头操作符
            // 计算当前点与起始点的距离
            dis = distance(point, start);
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
            cout << "\t" << "(" << start.x << "," << start.y << ")" << " to ";
            cout << "(" << point.x << "," << point.y << ")" << " dis:";
            cout << "(" << pointPtr->x << "," << pointPtr->y << ")" << " dis:"; // 使用 Point* 指针时，访问它的子对象需要用 -> 箭头操作符
            cout << dis << " ? ";
            cout << min_distance << endl;
        }
        // 将最小距离的点加入路径
        path[i] = map[min_index];
        // 标记该点为已访问
        visited[min_index] = 1;
        // 更新起始点为路径中的下一个点
        start = path[i];
        // 输出选择的点的信息
        cout << "Choosed:" << "<" << min_index << "> " << "(" << start.x << "," << start.y << ")" << endl;
    }
    // 返回路径
    delete[] visited;
    return path;
}

int main()
{
    // 创建坐标地图
    int n = 10;
    Point *map = create_map(n);     // create 创造；generate 生成

    // 用贪心算法计算最优路径
    int length = n;
    Point startPoint = Point{10, 13};      // 掌握定义 struct 结构体的方法
    Point *path = find_path_greepy(map, length, startPoint);
    // 输出最优路径
    cout << "Greedy Algorithm: " << endl;
    cout << "Length: " << length << endl;
    cout << "Path: (" << startPoint.x << ", " << startPoint.y << ")";
    for (int i = 0; i < length; i++)
    {
        cout << " -> (" << path[i].x << ", " << path[i].y << ")";
    }

    // 释放内存：在堆上分配的内存，如果不释放，将造成内存泄漏
    delete[] map;       // 分配和释放内存有两种方法：方法一，使用 C++ 的 new/delete；方法二，使用 C 的 malloc/calloc/free
    map = nullptr;      // 释放内存后，将指针设置为 nullptr，避免出现野指针：指向已释放的内存的指针，错误的使用野指针可能导致程序崩溃或产生【不可预测的结果】
    delete[] path;      // 鲁棒性(robustness)/健壮性：程序在【错误的输入】或【异常情况】下仍然能够【保持稳定】和【可靠】的运行
    path = nullptr;

    return 0;
}
