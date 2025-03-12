// 05-10-D04 一个月有多少天
#include <iostream>
using namespace std;

// 判断是否为闰年
bool IsLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) 
        || year % 400 == 0;
}
int main()
{
    int daysInMonths[] 
        = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year, month, days;
    cin >> year >> month;
    days = daysInMonths[month - 1];     // 取对应月份的天数
    if (month == 2 && IsLeapYear(year)) // 闰年2月有29天
        days++;                         // days = 29;
    cout << days << endl;
    return 0;
}