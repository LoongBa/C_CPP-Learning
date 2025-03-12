// 05-10-D02-学号分组(L3)
#include <iostream>
using namespace std;

int main()
{
    int studentId, group; // 学号，分组
    cin >> studentId;

    // 两次求模分组
    int tail = studentId % 10;  // last digit
    int remainder = tail % 3;   // 对 3 求模
    // 去掉条件表达式：利用初等数论同余原理的移位技巧
    group = (remainder + 2) % 3 + 1;

    cout << group << endl;
    return 0;
}