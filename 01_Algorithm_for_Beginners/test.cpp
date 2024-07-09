#include <iostream>
#include <iomanip>
using namespace std;

string numToChinese(int num) {
    string chineseNum[] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
    string chineseDigit[] = {"", "十"};
    if (num <= 10) {
        return chineseNum[num];
    } else if (num < 20) {
        return chineseDigit[1] + chineseNum[num % 10];
    } else {
        int tens = num / 10;
        int ones = num % 10;
        if (ones == 0) {
            return chineseNum[tens] + chineseDigit[1];
        } else {
            return chineseNum[tens] + chineseDigit[1] + chineseNum[ones];
        }
    }
}

int main()
{
    // 设置字符集为UTF-8
    system("chcp 65001>nul"); 

    string chineseNum[] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
    for (int j = 9; j >= 1; j--)
    {
        for (int i = 1; i <= j; i++)
        {
            int result = j * i;
            cout << setw(2) << chineseNum[i] << "乘" << setw(2) << chineseNum[j] << "等于" << setw(8) << numToChinese(result) << "  ";
        }
        cout << endl;
    }

    return 0;
}