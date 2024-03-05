#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 8

// 定义数据结构，便于理解代码
struct QueensInfo {
    int queensPlaced;   // 已放置的皇后数
    int queensFound;    // 已找到的解数
    int queensToRemove; // 需要移除的皇后数
};

/*
 * 函数名：printBoard
 * 功能：打印八皇后问题的棋盘
 * 参数：
 *     board: 二维数组表示棋盘
 * 返回值：无
 */
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

/*
 * 函数名：isSafe
 * 功能：检查在棋盘上放置皇后的位置是否安全
 * 参数：
 *     board: 二维数组，代表棋盘
 *     row: 当前要放置皇后的行数
 *     col: 当前要放置皇后的列数
 * 返回值：
 *     bool类型，表示当前位置是否安全
 */
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

/*
 * 函数名：solveNQueens_Recursive
 * 功能：递归求解N皇后问题
 * 参数：
 *     board: 二维数组表示棋盘
 *     row: 当前处理的行数
 * 返回值：布尔类型，表示是否成功找到解
 */
bool solveNQueens_Recursive(int board[N][N], int row) {
    if (row == N) {
        return true;
    }

    for (int col = 0; col < N; col++) { // 尝试在当前行的每一列放置皇后
        if (isSafe(board, row, col)) {  // 检查当前位置是否安全
            board[row][col] = 1;
            if (solveNQueens_Recursive(board, row + 1)) { // 递归处理下一行
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