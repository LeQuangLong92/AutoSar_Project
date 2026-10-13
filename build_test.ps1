$ErrorActionPreference = "Stop"
New-Item -ItemType Directory -Force build | Out-Null
$failed = 0

foreach ($t in Get-ChildItem test\test_*.c) {
    $name = $t.BaseName
    $mod  = $name -replace '^test_', ''
    gcc -std=c99 -Wall -Wextra -Isrc -Ivendor/unity "src/${mod}.c" $t.FullName vendor/unity/unity.c -o "build/${name}.exe"
    if ($LASTEXITCODE -ne 0) { Write-Host "BUILD FAILED: $name"; exit 1 }
    Write-Host "=== $name ==="
    & ".\build\${name}.exe"
    if ($LASTEXITCODE -ne 0) { $failed++ }
}
if ($failed -ne 0) { Write-Host "$failed test suite(s) FAILED"; exit 1 }
Write-Host "ALL SUITES PASSED"