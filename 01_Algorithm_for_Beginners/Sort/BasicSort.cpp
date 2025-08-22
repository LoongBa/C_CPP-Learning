#include <vector>
using namespace std;

// 冒泡排序
void bubbleSort(vector<int> &arr)
{
    if (arr.empty()) return;

    int n = arr.size();
    for (int i = 0; i < n - 1; i++) // 共需 n-1 轮（最后1个元素无需排序）
    {
        bool swapped = false; // 优化标志：记录本轮是否发生交换

        // 每轮遍历无序区（0~n-1-i），将最大元素移到末尾
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1]) // 相邻元素比较
            {
                swap(arr[j], arr[j + 1]); // 交换元素（大元素后移）
                swapped = true;
            }
        }
        // 优化：若本轮无交换，说明数组已有序，直接退出
        if (!swapped) break;
    }
}

// 选择排序
void selectionSort(vector<int> &arr)
{
    if (arr.empty()) return;
    
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) // 共需 n-1 轮（最后1个元素无需排序）
    {                    
        int min_idx = i;            // 记录无序区中最小元素的下标（初始为无序区头部）

        for (int j = i + 1; j < n; j++)     // 遍历无序区（i~n-1），寻找最小元素
            if (arr[j] < arr[min_idx])
                min_idx = j;                // 更新最小元素下标

        // 将最小元素交换到无序区头部（i位置）
        if (min_idx != i)
            swap(arr[i], arr[min_idx]);     // 优化：若最小元素已在头部，无需交换
    }
}