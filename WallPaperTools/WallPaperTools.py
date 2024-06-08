# 编写程序，读取 Windows 11 壁纸目录下的文件
# 如果文件名结尾不是 jpg，则复制到当前目录下的 WallPapers 目录下，并改名为 .jpg
import os
import shutil
from pathlib import Path

print("壁纸备份工具 V1.00 \n作者：xxx CopyRight 2024\n")
print("---------------------------")

# 读取环境变量 %USERPROFILE% 的值，用于构造完整路径
wallpaperDir = os.getenv("USERPROFILE") + "\\AppData\\Local\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\\Assets"

print("壁纸所在位置：", wallpaperDir)
os.system("start " + wallpaperDir)

# 创建目标目录如果它不存在（默认在当前目录下）
currentDir = Path.cwd()  # 获取当前目录
targetDir = currentDir / "WallPapers"
targetDir.mkdir(exist_ok=True)

# 执行命令，用资源管理器打开 WallPapers 文件夹
os.system("start " + str(targetDir))

# 输出完整路径，后续仅输出文件名
print("壁纸备份位置：", targetDir)

i = 0
# 遍历壁纸目录中的文件
for fileEntry in Path(wallpaperDir).iterdir():
    if fileEntry.is_file():
        filename = fileEntry.name
        extension = fileEntry.suffix

        # 检查文件扩展名是否不是 ".jpg"
        if extension != ".jpg":
            # 获取文件的创建日期
            print(i := i + 1, "\t源文件: ", filename)
            # 构造新的文件名，将 ".jpg" 扩展名添加到文件名中
            newFilename = filename.rsplit('.', 1)[0] + ".jpg"
            print("\t保存为 => ", newFilename, end="")
            newFilename = targetDir / newFilename

            # 将文件复制到目标目录，并使用新的文件名
            if newFilename.exists():  # 如果文件已经存在，则忽略
                print("\t\033[34m已存在，忽略\033[0m")
            else:
                shutil.copy2(fileEntry, newFilename)
                print("\t\033[32m备份完成\033[0m")

print("---------------------------")