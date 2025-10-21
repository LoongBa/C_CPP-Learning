// P5727 https://www.luogu.com.cn/problem/P5727
#include <iostream>
#include <stack>
using namespace std;
int main()
{
    int n;
    cin >> n;
    stack<int> s;
    s.push(n);
    while (n > 1)
    {
        if (n % 2 == 0)
            n /= 2;
        else
            n = 3 * n + 1;
        s.push(n);
    }
    while (!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
}