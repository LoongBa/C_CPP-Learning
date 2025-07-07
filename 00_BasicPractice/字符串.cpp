#include <iostream>
#include <string>
using namespace std;

int cha = 'a' - 'A';

/**
 * 将字符串转换为大写形式
 * @param str 要转换的字符串
 * @return 转换后的字符串
 */
string toUpperCase(string result) {
    for (char& c : result) {
        if (c >= 'a' && c <= 'z') {
            c = c - cha; // 将小写字母转换为大写字母
        }
    }
    return result;
}

/**
 * 将字符串转换为小写形式
 * @param str 要转换的字符串
 * @return 转换后的字符串
*/
string toLowerCase(const string& str) {
    string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c + cha; // 将大写字母转换为小写字母
        }
    }
    return result;
}

/**
 * 将字符串转换为大写形式
 * @param str 要转换的字符串
 * @return 转换后的字符串
 */
string toUpperCase2(const string& str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = result[i] - 'a' + 'A'; // 将小写字母转换为大写字母
        }
    }
    return result;
}

/**
 * 将字符串转换为小写形式
 * @param str 要转换的字符串
 * @return 转换后的字符串
*/
string toLowerCase2(const string& str) {
    string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a'; // 将大写字母转换为小写字母
        }
    }
    return result;
}


/**
 * @brief 主函数
 * @return 返回程序执行状态
 */
int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    string upper = toUpperCase(input); // 将输入字符串转换为大写形式
    string lower = toLowerCase(input); // 将输入字符串转换为小写形式

    cout << "Uppercase: " << upper << endl; // 输出大写形式的字符串
    cout << "Lowercase: " << lower << endl; // 输出小写形式的字符串

    return 0;
}