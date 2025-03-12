// 05-08-C05-找座位(L3)
#include <iostream>
using namespace std;

int main()
{
    const int count = 7; // 每行学生数
    int studentId;
    cin >> studentId;

    int row = studentId / count + 1; // 行号
    if (studentId % count == 0) // 整除，需要修正
        row--;
    // 列号，左移1位求余后右移1位
    int col = (studentId - 1) % count + 1;

    cout << row << " " << col << endl;

    return 0;
}