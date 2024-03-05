#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

// 检查迷宫中给定位置是否有效的函数
int isValid(int maze[ROWS][COLS], int row, int col) {
    // 检查位置是否在迷宫边界内且不是墙
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS && maze[row][col] == 0);
}

// 递归解决迷宫的函数
int solveMaze(int maze[ROWS][COLS], int row, int col, int endRow, int endCol) {
    // 基本情况：如果当前位置是目的地，则返回true
    if (row == endRow && col == endCol) {
        return 1;
    }

    // 检查当前位置是否有效
    if (isValid(maze, row, col)) {
        // 将当前位置标记为解路径的一部分
        maze[row][col] = 2;

        // 递归检查所有可能的方向：上、下、左、右
        if (solveMaze(maze, row - 1, col, endRow, endCol)) {
            return 1; // 尝试向上查找
        }
        if (solveMaze(maze, row + 1, col, endRow, endCol)) {
            return 1; // 尝试向下查找
        }
        if (solveMaze(maze, row, col - 1, endRow, endCol)) {
            return 1; // 尝试向左查找
        }
        if (solveMaze(maze, row, col + 1, endRow, endCol)) {
            return 1; // 尝试向右查找
        }

        // 如果没有方向通向目的地，则回溯
        maze[row][col] = 0;
    }

    return 0; // 未找到路径
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    system("chcp 65001>nul");

    // 定义迷宫
    int maze[ROWS][COLS] = {
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };

    // 定义起始和结束位置
    int startRow = 0, startCol = 0;
    int endRow = 4, endCol = 4;

    // 解决迷宫问题
    if (solveMaze(maze, startRow, startCol, endRow, endCol)) {
        printf("找到路径：\n");

        // 打印带有路径的迷宫
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (maze[i][j] == 2) {
                    printf("X "); // 路径
                } else {
                    printf("%d ", maze[i][j]); // 墙和空格
                }
            }
            printf("\n");
        }
    } else {
        printf("未找到路径。\n");
    }

    return 0;
}
