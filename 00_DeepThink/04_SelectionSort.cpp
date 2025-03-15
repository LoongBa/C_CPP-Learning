#include <iostream>
#include <vector>
using namespace std;

vector<int> SelectionSort(vector<int> unSort)
{
    for (int i = 0; i < unSort.size(); i++)
    {
        int min = unSort[i];
        int pos = i;
        for (int j = i; j < unSort.size(); j++)
        {
            if (unSort[j] < min)
            {
                min = unSort[j];
                pos = j;
            }
        }
        swap(unSort[i], unSort[pos]);
        // cout << min << endl;
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
    sorted = SelectionSort(unSort);
    cout << "等待排序：" << endl;
    printVector(unSort);
    cout << "排序结果：" << endl;
    printVector(sorted);
    return 0;
}