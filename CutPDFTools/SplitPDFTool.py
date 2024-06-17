# 打开指定的 PDF 文件，将其分割成多个图片文件，每页一个图片文件
# 对图片文件进行剪裁，去掉页眉和页脚，并拆分为两张图片
# 重新保存为 PDF 文件，每页为 A4 纸大小
# 保存的文件名为原文件名后加上 _A4.pdf
import os
import shutil
import sys
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
from fpdf import FPDF
from pdf2image import convert_from_path
from tqdm import tqdm

# 调试模式
Is_Debug = False

# PDF 转 Image 的默认分辨率
Pdf2Image_Default_Dpi = 300

# 自定义的输出函数
def WriteText(text, logLevel = 1):
    if Is_Debug:
        tqdm.write(text)
    elif logLevel > 1:
        tqdm.write(text)
    return

# 读取指定 PDF 文件，拆分为多个图片文件
def ExtractImagesFromPdfFile(pdfFilename):
    # 创建输出目录
    outputDir = pdfFilename.parent / pdfFilename.stem
    outputDir.mkdir(exist_ok=True)
    # 将 PDF 文件转换为图像
    images = convert_from_path(str(pdfFilename), dpi=Pdf2Image_Default_Dpi)
    # 遍历生成的图像
    for i, image in enumerate(images):
        # 生成图片文件名
        imageFilename = outputDir / f"{i+1:02d}.png"
        # 保存图片文件
        image.save(str(imageFilename), "PNG")
    return outputDir


# 剪裁图片文件，去掉页眉和页脚
def CropImageFile(imageFilename, leftMargin = 0, topMargin = 0, rightMargin = 0, bottomMargin = 0):
    # 创建输出目录
    is_reverseLeftAndRight = True
    outputDir = imageFilename.parent
    with Image.open(imageFilename) as img:
        width, height = img.size

        # 比例来自于相对 300DPI 的计算
        dpiRatio = 300 // Pdf2Image_Default_Dpi
        croppedImage = img.crop((leftMargin // dpiRatio, topMargin // dpiRatio, width - rightMargin // dpiRatio, height - bottomMargin // dpiRatio))

        # 生成剪裁后的图片文件名
        croppedImageFilename = outputDir / f"{imageFilename.stem}_cropped.png"
        croppedImage.save(croppedImageFilename, "PNG")
        # 将剪裁后的文件，分割成等宽的两个文件，保存为 _A4_01.png 和 _A4_02.png
        SplitCroppedIntoA4Files(croppedImageFilename)
    return croppedImageFilename


# 将剪裁后的文件，分割成等宽的两个文件，保存为 _A4_01.png 和 _A4_02.png
def SplitCroppedIntoA4Files(croppedImageFilename):
    with Image.open(croppedImageFilename) as img:
        width, height = img.size
        # 分割图片，每半页一张图片
        half_width = width // 2
        leftImage = img.crop((0, 0, half_width, height))
        rightImage = img.crop((half_width, 0, width, height))
        # 生成分割后的图片文件名
        leftImageFilename = (
            croppedImageFilename.parent / f"{croppedImageFilename.stem}_A4_01.png"
        )
        rightImageFilename = (
            croppedImageFilename.parent / f"{croppedImageFilename.stem}_A4_02.png"
        )
        leftImage.save(leftImageFilename, "PNG")
        rightImage.save(rightImageFilename, "PNG")

    return leftImageFilename, rightImageFilename


# 为指定图片底部正中位置添加页码数字：第 pageNumber 页/共 totalPages 页
def AddPageNumberIntoImage(imageFilename, totalPages, pageNumber, memo=" 龙爸特供勿外传"):
    with Image.open(imageFilename) as img:
        width, height = img.size
        # 计算字体大小
        font_size = height / Pdf2Image_Default_Dpi
        font_size_coefficient = 3  # adjust this value to change the font size
        font_size = int(font_size * font_size_coefficient)
        # 创建一个新的图像，比原图像高 20 像素
        newImg = Image.new("RGB", (width, height), (255, 255, 255))
        # 将原图像粘贴到新图像的顶部
        newImg.paste(img, (0, 0))
        # 在新图像底部正中位置添加页码数字
        draw = ImageDraw.Draw(newImg)
        font_path = Path(os.path.join(os.getenv("windir"), "fonts\\msyh.ttc"))
        if font_path.exists():
            font = ImageFont.truetype("msyh.ttc", font_size)
            text = f"第 {pageNumber} 页/共 {totalPages} 页"
            text = text + memo
        else:
            font = ImageFont.truetype("arial.ttf", font_size)
            text = f"{pageNumber} / {totalPages}"
        textWidth = font.getlength(text)
        draw.text(
            ((width - textWidth) // 2, height - font_size - 20),
            text,
            font=font,
            fill=(0, 0, 0),
        )
        # 保存新图像
        newImg.save(imageFilename)

    return imageFilename


# 将指定目录里，被剪裁过的图片文件重新保存为指定的 PDF 文件
def MergeImagesAsPDFFile(imageDir):
    A4Folder = imageDir.parent / f"_A4_"
    A4Folder.mkdir(exist_ok=True)
    pdfFilename = A4Folder / f"{imageDir.stem}_A4.pdf"
    # 创建一个空白 PDF 文件
    pdf = FPDF()
    images = list(imageDir.glob("*_cropped_A4_*.png"))
    totalPages = len(images)
    pageNumber = 0
    # 遍历图片目录中的所有图片文件
    for imageFilename in images:
        pageNumber += 1
        AddPageNumberIntoImage(imageFilename, totalPages, pageNumber)
        # 将图片添加到 PDF 文件中
        pdf.add_page()
        pdf.image(str(imageFilename), 0, 0, 210, 297)  # 使用 A4 纸大小

        with Image.open(imageFilename) as img:
            width, height = img.size
            WriteText(
                f"\t\t\t第{pageNumber}页/共{totalPages}页 {imageFilename.name}\t{width}x{height}"
            )
    # 保存 PDF 文件
    pdf.output(str(pdfFilename), "F")

    return pdfFilename


# 读取指定目录中的所有 PDF 文件，调用相关函数完成处理
def ProcessPDFFiles(pdfDir, keywordsInName = "", leftMargin = 0, topMargin = 0, rightMargin = 0, bottomMargin = 0, reverseLeftAndRight = True):
    if not pdfDir.exists():
        WriteText(f"\33[31m【错误】文件夹不存在：‘{pdfDir}’\33[0m", 3)
        return

    WriteText(f"\r\n\033[32m开始处理文件夹中的 PDF 文件：{pdfDir}\33[0m", 3)
    if len(keywordsInName) > 0:
        WriteText(f"\t包含关键字‘\33[35m{keywordsInName}\33[0m’\33[0m", 3)
    
    count = 0
    ignore = 0
    # 遍历指定目录中的所有 PDF 文件
    pdfFiles = list(pdfDir.glob("*.pdf"))
    total = len(pdfFiles)
    pbar = tqdm(pdfFiles, total=total)
    for pdfFilename in pbar:
        # 忽略已经处理过的文件
        if "_A4" in pdfFilename.stem:
            continue

        # 忽略没有包含指定关键字的文件
        if len(keywordsInName) > 0 and not (keywordsInName in pdfFilename.stem):
            ignore += 1
            WriteText(f"\t\033[35m忽略文件\033[0m ‘{pdfFilename.name}’。\t{ignore:02d}", -1)
            continue

        count += 1
        pbar.set_description(f"处理 PDF 文件 ‘{pdfFilename.name}’")
        # WriteText(f"{count:02d} 处理 PDF 文件 ‘{pdfFilename.name}’ ...\t 指定 DPI = {Pdf2Image_Default_Dpi}")
        # 提取 PDF 文件图片
        outputDir = ExtractImagesFromPdfFile(pdfFilename)
        WriteText(f"\t{count:02d} 提取 PDF 文件图片 ‘{pdfFilename.name}’ \033[32m成功。\033[0m")
        # 剪裁图片文件
        for imageFilename in outputDir.glob("*.png"):
            # 排除已经剪裁过的图片文件
            if "_cropped" in imageFilename.stem:
                continue
            
            # 试卷的奇数页和偶数页的左右边距不同
            if reverseLeftAndRight:
                number = int(imageFilename.stem.split(".")[0])
                if number % 2 == 1:
                    cropedFile = CropImageFile(imageFilename, leftMargin, topMargin, rightMargin, bottomMargin)
                else:   # 偶数页，颠倒左右边距
                    cropedFile = CropImageFile(imageFilename, rightMargin, topMargin, leftMargin, bottomMargin)
            else:
                cropedFile = CropImageFile(imageFilename)

            WriteText(
                f"\t\t剪裁图片文件 {imageFilename.name} 为 {cropedFile.name} \033[32m成功。\033[0m"
            )
        # 重新保存为 PDF 文件
        newPdfFilename = MergeImagesAsPDFFile(outputDir)
        # 删除临时目录 outputDir
        if not Is_Debug:
            shutil.rmtree(outputDir)
        WriteText(
            f"\t\t保存剪裁后的图片文件为 ‘{newPdfFilename.name}’ \033[32m成功。\033[0m\r\n"
        )
    WriteText(f"\t\033[32m处理完成，共处理 {count} 个，忽略 {ignore} 个。\033[0m\r\n", 3)    
    return

# 主程序
def main():
    if len(sys.argv) < 2:
        path = os.path.dirname(os.path.abspath(__file__))
        path = "D:\\_Dev_\\_Repos_\\Github\\_CoffeeScholar_\\C_CPP-Learning\\CutPDFTools\\test\\"
        # print("使用方法: python cutPDFfiles.py <包含 PDF 文件的文件夹路径>")
    else:
        path = sys.argv[1]
        if not os.path.isabs(path):  # 如果路径不是绝对路径
            path = os.path.join(os.path.dirname(os.path.abspath(__file__)), path)  # 将路径转换为绝对路径
        if not os.path.exists(path):  # 如果路径不存在
            print(f"路径 {path} 不存在。")
            return

    # 名字包含“答案”的文件，左右边距相同
    ProcessPDFFiles(Path(path), "答案", 160, 160, 160, 160, False)  # 不需要颠倒奇偶页的左右边距
    # 名字包含“正文”的文件，是正式试卷，左右边距不同
    ProcessPDFFiles(Path(path), "正文", 300, 165, 160, 160, True)   # 需要颠倒奇偶页的左右边距
    
    # 用同一套边距参数处理所有文件——需要人为将不同文件分别保存到不同文件夹，然后处理
    # ProcessPDFFiles(Path(path), "", 300, 165, 160, 160, True)

if __name__ == "__main__":
    main()
