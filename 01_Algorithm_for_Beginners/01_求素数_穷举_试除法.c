#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * 判断一个数是否为素数
 * 
 * @param num 要判断的数
 * @return 如果是素数，返回 true；否则返回 false
 */
bool isPrime(int num) {
    if (num <= 1) { // 如果数小于等于 1，则不是素数
        return false;
    }
    
    if (num == 2 || num == 3) { // 如果数等于 2 或 3，则是素数
        return true;
    }
    
    if (num % 2 == 0 || num % 3 == 0) { // 如果数能被 2 或 3 整除，则不是素数
        return false;
    }
    
    for (int i = 5; i * i <= num; i += 6) { // 从 5 开始遍历到 sqrt(num)，步长为 6
        if (num % i == 0 || num % (i + 2) == 0) { // 如果数能被 i 或 (i+2) 整除，则不是素数
            return false;
        }
    }
    
    return true;
}

int main() {
    // 设置控制台输出为UTF-8编码，以支持中文输出
    system("chcp 65001>nul"); 

    printf("100以内的素数：\n");
    
    for (int i = 2; i <= 100; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    
    printf("\n");
    
    return 0;
}
