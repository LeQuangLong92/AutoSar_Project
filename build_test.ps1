$ErrorActionPreference = "Stop"
New-Item -ItemType Directory -Force build | Out-Null

gcc -std=c99 -Wall -Wextra -Isrc -Ivendor/unity `
    src/can_signal.c test/test_can_signal.c vendor/unity/unity.c `
    -o build/test_can_signal.exe

if ($LASTEXITCODE -ne 0) { Write-Host "BUILD FAILED"; exit 1 }
& .\build\test_can_signal.exe