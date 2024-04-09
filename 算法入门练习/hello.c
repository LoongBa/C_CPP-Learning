#include <stdio.h>
#include <stdlib.h>
//#include <fcntl.h>

int main() {
    system("chcp");
    //system("pause");
    system("chcp 65001>nul");

    // 更改控制台输出模式为宽字符模式
    //_setmode(_fileno(stdout), _O_U16TEXT);
    printf("Hello World！你好，我来了！");
}
