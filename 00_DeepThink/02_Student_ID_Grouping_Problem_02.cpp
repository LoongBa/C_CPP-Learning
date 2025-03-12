// 05-10-D02-学号分组(L3)
#include <iostream>
using namespace std;

int main()
{
    int studentId, group;  // 学号，分组
    cin >> studentId;
    
    // 判断尾号
    int tail = studentId % 10;              // last digit
    if (tail == 1 || tail == 4 || tail == 7)
        group = 1;
    else if (tail == 2 || tail == 5 || tail == 8)
        group = 2;
    else
        group = 3;
    
    cout << group << endl;
    return 0;
}