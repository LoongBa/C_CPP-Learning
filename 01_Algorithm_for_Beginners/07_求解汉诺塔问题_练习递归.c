#include <stdio.h>
#include <stdlib.h>

// 用递归的方式解决汉诺塔问题
void hanoi_Recursive(int n, char source, char target, char auxiliary) {
    // 基本情况：如果只有一个盘子，直接从源柱移动到目标柱
    if (n == 1) {
        printf("将第 1 个盘子从柱子 %c 移动到柱子 %c\n", source, target);
        return;
    }

    // 将 n-1 个盘子从源柱移动到辅助柱，以目标柱作为辅助柱
    hanoi_Recursive(n - 1, source, auxiliary, target);

    // 将第 n 个盘子从源柱移动到目标柱
    printf("将第 %d 个盘子从柱子 %c 移动到柱子 %c\n", n, source, target);

    // 将 n-1 个盘子从辅助柱移动到目标柱，以源柱作为辅助柱
    hanoi_Recursive(n - 1, auxiliary, target, source);
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    system("chcp 65001>nul");

    int n = 3; // 盘子的数量
    char source = 'A'; // 源柱的名称
    char target = 'C'; // 目标柱的名称
    char auxiliary = 'B'; // 辅助柱的名称

    printf("\n递归解法:\n");
    hanoi_Recursive(n, source, target, auxiliary);

    return 0;
}
