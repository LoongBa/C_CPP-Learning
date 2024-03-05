#include <stdio.h>
#include <stdlib.h>

// Function to calculate the greatest common divisor (GCD) using iterative approach
int gcd_Iterative(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

// Function to calculate the greatest common divisor (GCD) using recursive approach
int gcd_Recursive(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd_Recursive(b, a % b);
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    system("chcp 65001>nul");

    int a, b;
    printf("请输入两个整数：");
    scanf("%d %d", &a, &b);

    int result_iterative = gcd_Iterative(a, b);
    int result_recursive = gcd_Recursive(a, b);

    printf("迭代法求得的最大公约数为：%d\n", result_iterative);
    printf("递归法求得的最大公约数为：%d\n", result_recursive);

    return 0;
}
