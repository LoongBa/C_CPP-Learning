// P1161 开灯
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
int main()
{
    map<int, int> light;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        double a;
        int t;
        cin >> a >> t;
        for (int j = 1; j <= t; j++)
        {
            int num = a * j;
            light[num]++;
        }
    }
    for (auto i : light)
    {
        if (i.second % 2 == 1)
        {
            cout << i.first << endl;
            break;
        }
    }
    return 0;
}