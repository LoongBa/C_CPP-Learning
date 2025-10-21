// P5662 [CSP-J2019] 纪念品
// https://www.luogu.com.cn/problem/P5662
// 解题思路V2：完全背包
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX_M = 10000; // 题目约定的最大金币数
int main()
{
    int T, N, M;
    cin >> T >> N >> M;

    vector<vector<int>> price(T + 1, vector<int>(N + 1));
    for (int i = 1; i <= T; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> price[i][j];
        }
    }

    int money = M;

    // 逐天处理
    for (int day = 1; day < T; day++)
    {
        // dp[k]: 使用k枚金币进行交易后，下一天能获得的最大金币数
        vector<int> dp(MAX_M + 1, 0);

        // 初始化为当前金币数（不交易的情况）
        for (int k = 0; k <= money; k++)
        {
            dp[k] = k;
        }

        // 对每种纪念品进行完全背包
        for (int item = 1; item <= N; item++)
        {
            int cost = price[day][item];      // 当天价格
            int value = price[day + 1][item]; // 下一天价格

            // 完全背包：正序遍历
            for (int k = cost; k <= money; k++)
            {
                // 状态转移：比较不买和买的情况
                dp[k] = max(dp[k], dp[k - cost] + value);
            }
        }

        // 更新总金币数为最大可能值
        money = *max_element(dp.begin(), dp.end());
    }

    cout << money << endl;
    return 0;
}