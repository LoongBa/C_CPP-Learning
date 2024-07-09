#include <stdio.h>

// 使用迭代计算斐波那契数列的函数
void fibonacci_Iterative(int n) {
    int fib[n]; // 用于存储斐波那契数列的数组
    fib[0] = 0; // 第一个斐波那契数
    fib[1] = 1; // 第二个斐波那契数

    // 计算并存储剩余的斐波那契数
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // 打印斐波那契数列
    printf("使用迭代计算的斐波那契数列:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");
}

// 使用递归计算斐波那契数列的函数
int fibonacci_Recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_Recursive(n - 1) + fibonacci_Recursive(n - 2);
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    system("chcp 65001>nul");
    
    int n = 10; // 要生成的斐波那契数的数量

    // 使用迭代计算并打印斐波那契数列
    fibonacci_Iterative(n);

    // 使用递归计算并打印斐波那契数列
    printf("使用递归计算的斐波那契数列:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci_Recursive(i));
    }
    printf("\n");

    return 0;
}
