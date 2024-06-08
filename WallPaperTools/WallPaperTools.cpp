// 编写程序，读取 Windows 11 壁纸目录下的文件
// 如果文件名结尾不是 jpg，则复制到当前目录下的 WallPapers 目录下，并改名为 .jpg
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;

int main()
{
    system("chcp 65001>nul");
    cout << "壁纸备份工具 V1.00 \r\n作者：xxx CopyRight 2024\r\n"
         << endl;
    cout << "---------------------------" << endl;

    string wallpaperDir = getenv("USERPROFILE"); // 读取环境变量 %USERPROFILE% 的值，用于构造完整路径
    wallpaperDir += "\\AppData\\Local\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\\Assets";

    cout << "壁纸所在位置：" << wallpaperDir << endl;
    string command = "start " + wallpaperDir;
    system(command.c_str());

    // 创建目标目录如果它不存在（默认在当前目录下）
    string currentDir = fs::current_path().string(); // 获取当前目录
    string targetDir = currentDir + "\\WallPapers";
    fs::create_directory(targetDir);
    // 执行命令，用资源管理器打开 WallPapers 文件夹
    command = "start " + targetDir;
    system(command.c_str());

    // 输出完整路径，后续仅输出文件名
    cout << "壁纸备份位置：" << targetDir << endl;

    int i = 0;
    // 遍历壁纸目录中的文件
    for (const auto &fileEntry : fs::directory_iterator(wallpaperDir))
    {
        if (fileEntry.is_regular_file())
        {
            string filename = fileEntry.path().filename().string();
            string extension = fileEntry.path().extension().string();

            // 检查文件扩展名是否不是 ".jpg"
            if (extension != ".jpg")
            {
                // // 获取文件的创建日期
                cout << ++i << "\t源文件: " << filename << endl;
                // 构造新的文件名，将 ".jpg" 扩展名添加到文件名中
                string newFilename = filename.substr(0, filename.find_last_of('.')) + ".jpg";
                cout << "\t保存为 => " << newFilename;
                newFilename = targetDir + "/" + newFilename;

                // 将文件复制到目标目录，并使用新的文件名
                if (fs::exists(newFilename)) // 如果文件已经存在，则忽略
                {
                    cout << "\t\033[34m已存在，忽略\033[0m" << endl;
                }
                else
                {
                    fs::copy_file(fileEntry.path(), newFilename);
                    cout << "\t\033[32m备份完成\033[0m" << endl;
                }
            }
        }
    }
    cout << "---------------------------" << endl;

    return 0;
}
