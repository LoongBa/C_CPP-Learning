#include <iostream>
#include <sys/stat.h>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// 函数用于获取文件的最后修改时间
time_t getLastModifiedTime(const string& filename) {
    struct stat fileInfo;
    if (stat(filename.c_str(), &fileInfo) != 0) {
        return 0; // 文件不存在或无法获取信息
    }
    return fileInfo.st_mtime; // 返回文件的最后修改时间
}

// 函数用于将文件名的扩展名替换为 .exe
string replaceExtensionWithExe(const string& filename) {
    size_t lastDot = filename.find_last_of(".");
    if (lastDot == string::npos) {
        return filename + ".exe";
    }
    return filename.substr(0, lastDot) + ".exe";
}

int main(int argc, char* argv[]) {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // 设置控制台编码为 UTF-8
    #endif

    if (argc < 2) {
        cerr << "用法: " << argv[0] << " <源文件>" << endl;
        return 1;
    }

    string sourceFile = argv[1];
    string executable = replaceExtensionWithExe(sourceFile);

    time_t sourceLastModified = getLastModifiedTime(sourceFile);
    time_t executableLastModified = getLastModifiedTime(executable);

    if (sourceLastModified > executableLastModified || executableLastModified == 0) {
        cout << "源文件已更新或可执行文件不存在，开始编译..." << endl;

        string command = "g++ -o " + executable + " " + sourceFile;
        int result = system(command.c_str());
        if (result == 0) {
            cout << "编译完成。" << endl;
        } else {
            cerr << "编译失败。" << endl;
        }
    } else {
        cout << "源文件未更新，无需编译。" << endl;
    }

    return 0;
}