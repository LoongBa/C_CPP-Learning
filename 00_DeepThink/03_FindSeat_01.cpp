//05-08-C05-找座位(L3)
#include <iostream>
using namespace std;

int main()
{
    const int count = 7; // 每行学生数
    int studentId;
    cin >> studentId;

    int row = studentId / count;    // 行号
    if (studentId % count != 0)     // 整除，修正
        row++;
    int col = studentId % count;    // 列号
    if (col == 0)                   // 整除，修正
        col = count;

    cout << row << " " << col << endl;

    return 0;
}