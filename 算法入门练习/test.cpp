#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string str = "Hello, World!";
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout << str << endl;
    return 0;
}
