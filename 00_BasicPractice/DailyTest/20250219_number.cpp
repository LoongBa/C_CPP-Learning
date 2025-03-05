#include <iostream>
using namespace std;

// 使用数学方法判断一个整数是否为回文数
bool isPalindromeNumber(int num) {
    if (num < 0) return false; // 负数不是回文数
    int reversedNum = 0, originalNum = num, remainder;
    while (num != 0) {
        remainder = num % 10;
        reversedNum = reversedNum * 10 + remainder;
        
        num /= 10;
    }
    return originalNum == reversedNum;
}

int main() {
    int num;
    cin >> num;
    if (num < 100 || num >= 1000) { // 范围检查
        return 1; // 返回错误码
    }

    // 使用数学方法判断回文数
    if (isPalindromeNumber(num)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
