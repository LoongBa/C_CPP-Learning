#include <stdio.h>
#include <stdlib.h>

// 计算 n 的阶和
int calculateSum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

// 计算 n 的阶乘
int calculateFactorial(int n) {
    int factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    return factorial;
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    system("chcp 65001>nul");

    int n = 5;
    int sum = calculateSum(n);
    int factorial = calculateFactorial(n);

    // 输出结果
    printf("5 的阶和为：%d\n", sum);
    printf("5 的阶乘为：%d\n", factorial);

    return 0;
}
