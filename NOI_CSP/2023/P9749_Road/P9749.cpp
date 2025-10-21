// P9749 [CSP-J 2023] 公路
// https://www.luogu.com.cn/problem/P9749
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    cin >> n >> d;

    vector<ll> distances(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> distances[i];

    vector<ll> prices(n);
    for (int i = 0; i < n; ++i) cin >> prices[i];

    ll totalCost = 0;
    ll lowestPrice = prices[0];
    ll restDistance = 0;

    for (int i = 0; i < n - 1; ++i) {
        ll distance = distances[i] - restDistance;
        ll fuel = (distance + d - 1) / d;   // 向上取整
        totalCost += fuel * lowestPrice;
        restDistance = fuel * d - distance;

        if (lowestPrice > prices[i + 1]) {
            lowestPrice = prices[i + 1];
        }
    }

    cout << totalCost << '\n';
    return 0;
}