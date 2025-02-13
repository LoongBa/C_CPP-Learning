#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int price;
    // 输入购物金额
    cin >> price; 
    // 初始化折扣后的金额
    double amount = price; 

    // 根据购物金额应用不同的折扣
    if (price >= 500) {
        amount *= 0.6;
    } else if (price >= 400) {
        amount *= 0.7;
    } else if (price >= 300) {
        amount *= 0.8;
    } else if (price >= 200) {
        amount *= 0.9;
    }

    // 输出折扣后的金额，保留小数点后一位
    // set 设置; precision 精度; fixed 固定小数点
    cout << fixed << setprecision(1) << amount << endl;

    return 0;
}