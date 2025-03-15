#include <iostream>
#include <vector>
using namespace std;
/// @brief 冒泡排序：注意，修改了原始数组
/// @param unSort
/// @return
vector<int> BubbleSort(vector<int> unSort)
{
    int x, size = unSort.size();
    bool isSorted = false;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (unSort[j] > unSort[j + 1])
            {
                swap(unSort[j], unSort[j + 1]);
                isSorted = true;
            }
        }
        if (!isSorted)
            break;
    }
    return unSort;
}

void printVector(vector<int> v)
{
    for (int i : v)
        cout << i << ' ';
    cout << endl;
}

int main()
{
    system("chcp 65001 > nul");
    vector<int> unSort = {1, 4, 7, 2, 5, 3, 6, 8, 9, 0};
    vector<int> sorted;
    sorted = BubbleSort(unSort);
    cout << "等待排序：" << endl;
    printVector(unSort);
    cout << "排序结果：" << endl;
    printVector(sorted);
    return 0;
}