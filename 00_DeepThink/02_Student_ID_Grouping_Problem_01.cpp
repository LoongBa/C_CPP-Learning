// 05-10-D02-学号分组(L3)
#include <iostream>
using namespace std;

int main()
{
    int studentId;  // 学号
    cin >> studentId;
    
    // 判断尾号
    int tail = studentId % 10;      // last digit
    if (tail == 1 || tail == 4 || tail == 7)
        cout << 1 << endl;
    else if (tail == 2 || tail == 5 || tail == 8)
        cout << 2 << endl;
    else
        cout << 3 << endl;
    
    return 0;
}