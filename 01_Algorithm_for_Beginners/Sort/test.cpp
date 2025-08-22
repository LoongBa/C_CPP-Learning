#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 冒泡排序
int main()
{
    string name = "'Jhon Doe'";
    auto pos = name.find("o");
    if (pos >= 0)
        cout << name << " Found 'o' at " << pos << endl;
    pos = name.find("k");
    if (pos >= 0)
        cout << "Found 'k' at " << pos << endl;
    else if (pos < 0)
        cout << "Not Found: " << pos << endl;

    if (pos == -1)
        cout << "Not Found: " << pos << endl;
}