// 05-10-D04 一个月有多少天
#include <iostream>
using namespace std;

int main()
{
    int year, month, days;
    cin >> year >> month;
    // 判断大月还是小月
    if (month == 1 || month == 3 || month == 5 
        || month == 7 || month == 8 || month == 10 || month == 12)
        days = 31;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        days = 30;
    else if (month == 2)
        // 判断闰年
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            days = 29;
        else
            days = 28;
    cout << days << endl;

    return 0;
}