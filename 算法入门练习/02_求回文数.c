#include <stdio.h>
#include <stdlib.h>

/**
 * 判断一个整数是否为回文数
 * 
 * @param number 要判断的整数
 * @return 如果是回文数，返回1；否则，返回0
 */
int isPalindrome(int number) {
    int originalNumber = number; // 保存原始数值
    int reversedNumber = 0; // 反转后的数值
    
    while (number != 0) {
        int remainder = number % 10; // 获取最后一位数字
        reversedNumber = reversedNumber * 10 + remainder; // 将最后一位数字添加到反转数值中
        number /= 10; // 去掉最后一位数字
    }
    
    return originalNumber == reversedNumber; // 判断原始数值和反转数值是否相等
}

int main() {
    system("chcp 65001>nul");

    int count = 0; // 计数器，用于统计回文数的个数
    for (int i = 1000; i <= 9999; i++) {
        if (isPalindrome(i)) { // 判断当前数值是否为回文数
            printf("%d 是一个回文数\n", i); // 打印回文数
            count++; // 计数器加一
        }
    }
    
    printf("共有回文数： %d\n", count); // 打印回文数的总个数
    
    return 0;
}
