#include <iostream>
#include <string>
using namespace std;

int main() {
    string in;
    cin >> in;

    int mode1Player1 = 0, mode1Player2 = 0, mode2Player1 = 0, mode2Player2 = 0;

    // 处理11分制
    for (int i = 0; i < in.size(); i++) {
        if (in[i] == 'W') {
            mode1Player1++;
        } else if (in[i] == 'L') {
            mode1Player2++;
        } else if (in[i] == 'E') {
            cout << "11     " << mode1Player1 << ':' << mode1Player2 << endl;
            break;
            
        }

        if ((mode1Player1 >= 11 || mode1Player2 >= 11) && 
            (abs(mode1Player1 - mode1Player2) >= 2)) {
            cout << "11     " << mode1Player1 << ':' << mode1Player2 << endl;
            mode1Player1 = 0;
            mode1Player2 = 0;
        }
    }

    cout << endl;

    // 处理21分制
    for (int i = 0; i < in.size(); i++) {
        if (in[i] == 'W') {
            mode2Player1++;
        } else if (in[i] == 'L') {
            mode2Player2++;
        } else if (in[i] == 'E') {
            cout << "21     " << mode2Player1 << ':' << mode2Player2 << endl;
            break;
        }

        if ((mode2Player1 >= 21 || mode2Player2 >= 21) && 
            (abs(mode2Player1 - mode2Player2) >= 2)) {
            cout << "21     " << mode2Player1 << ':' << mode2Player2 << endl;
            mode2Player1 = 0;
            mode2Player2 = 0;
        }
    }

    return 0;
}
