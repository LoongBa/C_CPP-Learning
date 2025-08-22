// P1161
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<bool> light(1, 0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        double a;
        int t;
        cin >> a >> t;
        int maxnum = a * t;
        if (maxnum > light.size() - 1)
            light.resize(maxnum + 1, false);
        for (int j = 1; j <= t; j++)
        {
            int num = a * j;
            light[num] = !light[num];
        }
    }
    for (int i = 1; i <= light.size(); i++)
    {
        if (light[i])
        {
            cout << i << endl;
            break;
        }
    }
    return 0;
}