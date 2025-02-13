#include <bits/stdc++.h>

using namespace std;

int main()
{
    unordered_set<string> cards;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string card;
        cin >> card;
        if (cards.find(card) != cards.end())
        {
            cards.emplace(card);
        }
    }

    cout << 52 - cards.size() << endl;
    return 0;
}
