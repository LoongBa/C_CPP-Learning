// P8814 [CSP-J 2022] 解密
// https://www.luogu.com.cn/problem/P8814
#include <iostream>
#include <cmath>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k;
    cin >> k;
    
    while (k--) {
        ll n, e, d;
        cin >> n >> e >> d;
        
        // 计算 p + q
        ll b = n - e * d + 2;
        // x^2 + bx + n = 0
        // x = (-b ± sqrt(b^2 - 4n)) / 2
        // delta = b^2 - 4n

        // 计算判别式
        ll delta = b * b - 4 * n;
        
        if (delta < 0) {
            cout << "NO\n";
            continue;
        }
        
        // 检查 delta 是否为完全平方数
        ll sqrt_delta = sqrt(delta);
        if (sqrt_delta * sqrt_delta != delta) {
            cout << "NO\n";
            continue;
        }
        
        // 计算 p 和 q
        // p = (-b + sqrt(delta)) / 2
        // q = (-b - sqrt(delta)) / 2
        ll p = (b - sqrt_delta) / 2;
        ll q = (b + sqrt_delta) / 2;
        
        // 验证解的正确性
        if (p > 0 && q > 0 && p * q == n) {
            cout << p << " " << q << "\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}