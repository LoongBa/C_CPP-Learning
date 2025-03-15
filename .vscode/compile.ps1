# 获取文件路径和名称
$sourceFile = $args[0]
$exePath = [System.IO.Path]::ChangeExtension($sourceFile, ".exe")

# 检查源文件是否比可执行文件新，或者可执行文件是否存在
if ((Get-Item $sourceFile).LastWriteTime -gt (Get-Item $exePath -ErrorAction SilentlyContinue).LastWriteTime -or !(Test-Path $exePath)) {
    Write-Output "正在编译 $sourceFile..."
    & "g++.exe" -fdiagnostics-color=always -g $sourceFile -o $exePath

    if ($?) {
        Write-Output "编译成功：$exePath"
    } else {
        Write-Output "编译失败，请检查错误信息。"
    }
} else {
    Write-Output "可执行文件是最新的，无需重新编译。"
}