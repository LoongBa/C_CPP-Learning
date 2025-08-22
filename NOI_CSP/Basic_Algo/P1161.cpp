// P1161
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> light(1, 0);
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
            if(light.size() <= num)
                light.resize(num + 1, 0);
            light[num]++;
        }
    }
    for (int i = 1; i <= light.size(); i++)
    {
        if (light[i] % 2 == 1)
        {
            cout << i << endl;
            break;
        }
    }
    return 0;
}