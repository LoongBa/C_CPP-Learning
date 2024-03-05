#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 8

struct QueensInfo {
    int queensPlaced;
    int queensFound;
    int queensToRemove;
};

// 打印棋盘
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                printf("皇后 ");
            } else {
                printf("____ ");
            }
        }
        printf("\n");
    }
}

// 检查当前位置是否安全
bool isSafe(const int board[N][N], int row, int col) {
    int i, j;

    for (i = 0; i < row; i++) {
        if (board[i][col])
            return false;
        if (col - row + i >= 0 && board[i][col - row + i])
            return false;
        if (col + row - i < N && board[i][col + row - i])
            return false;
    }

    return true;
}

// 递归函数来解决八皇后问题
bool solveNQueens_Recursive(int board[N][N], int row) {
    if (row == N) {
        return true;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            if (solveNQueens_Recursive(board, row + 1)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    // 设置控制台输出为 UTF-8 编码
    system("chcp 65001>nul");

    //创建一个大小为N*N的二维数组board，并初始化所有元素为0
    int board[N][N] = {0};

    if (solveNQueens_Recursive(board, 0)) {
        printf("递归找到一个解：\n");
        printBoard(board);
    } else {
        printf("没有找到解。\n");
    }

    return 0;
}