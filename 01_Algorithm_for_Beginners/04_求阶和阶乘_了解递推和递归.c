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

// 计算 n 的阶和
int calculateSum_Recursive(int n) {
    if (n == 1) { // 1 的阶和为 1，终止递归
        return 1;
    } else {
        return n + calculateSum_Recursive(n - 1); // 递归调用自己，求 n-1 的阶和
    }
}

// 计算 n 的阶乘
int calculateFactorial_Recursive(int n) {
    if (n == 0) {   // 0 的阶乘为 1，终止递归
        return 1;
    } else {
        return n * calculateFactorial_Recursive(n - 1); // 递归调用自己，求 n-1 的阶乘
    }
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    system("chcp 65001>nul");

    int n = 5;
    // 输出结果
    printf("5 的阶和为：%d\n", calculateSum(n));
    printf("5 的阶乘为：%d\n", calculateFactorial(n));
    printf("5 的阶和为（递归）：%d\n", calculateSum_Recursive(n));
    printf("5 的阶乘为（递归）：%d\n", calculateFactorial_Recursive(n));

    return 0;
}
