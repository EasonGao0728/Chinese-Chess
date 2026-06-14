$ErrorActionPreference = "Stop"

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $projectRoot

$mingwBin = "C:\Users\xiche\AppData\Local\Programs\WinLibsManual\mingw64\bin"
$gpp = Join-Path $mingwBin "g++.exe"

if (-not (Test-Path $gpp)) {
    Write-Host "[Error] g++ not found:" -ForegroundColor Red
    Write-Host "        $gpp" -ForegroundColor Red
    exit 1
}

$env:Path = "$mingwBin;$env:Path"
chcp 65001 > $null

Write-Host "[1/2] Building..."
& $gpp "@build.rsp"
if ($LASTEXITCODE -ne 0) {
    Write-Host "[Error] Build failed." -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host "[2/2] Running ChineseChess.exe..."
& ".\ChineseChess.exe"
exit $LASTEXITCODE
