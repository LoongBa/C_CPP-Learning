// 05-10-D02-学号分组(L3)
#include <iostream>
using namespace std;

int main()
{
    // 查表法：尾号对应的分组表
    int group_table[] = {3, 1, 2, 3, 1, 2, 3, 1, 2, 3};  
    int studentId;  // 学号
    cin >> studentId;
    
    int tail = studentId % 10;              // last digit
    int group = group_table[tail];          // 查表得到分组
    
    cout << group << endl;
    return 0;
}