#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Function to check if a number is an Armstrong number
// 检查一个数是否为阿姆斯特朗数的函数
bool isArmstrongNumber(int number) {
    int originalNumber = number;
    int sum = 0;
    int digit;

    // Calculate the sum of the cubes of each digit
    // 计算每个数字的立方和
    while (number > 0) {
        digit = number % 10;
        sum += digit * digit * digit;
        number /= 10;
    }

    // Check if the sum is equal to the original number
    // 检查和是否等于原始数字
    if (sum == originalNumber) {
        return true;
    } else {
        return false;
    }
}

int main() {
    system("chcp 65001>nul");
    printf("水仙花数 Armstrong Numbers:\n");
    int i;
    // Check numbers within the range of 10000
    // 检查在10000范围内的数字
    for (i = 0; i <= 10000; i++) {
        if (isArmstrongNumber(i)) {
            printf("%d ", i);
        }
    }

    return 0;
}
