param([string]$Module = "can_signal")

$ErrorActionPreference = "Stop"
New-Item -ItemType Directory -Force build | Out-Null
Remove-Item build\*.gcda, build\*.gcno -ErrorAction SilentlyContinue

$test = "test_$Module"

# Chỉ module cần đo mới biên dịch với --coverage
gcc --coverage -O0 -g -std=c99 -Wall -Wextra -Isrc -c "src/$Module.c" -o "build/$Module.o"
gcc -std=c99 -Isrc -Ivendor/unity -c "test/$test.c" -o "build/$test.o"
gcc -std=c99 -Ivendor/unity -c vendor/unity/unity.c -o build/unity.o
gcc --coverage "build/$Module.o" "build/$test.o" build/unity.o -o "build/${test}_cov.exe"

& ".\build\${test}_cov.exe"
gcov -b -c -o build "src/$Module.c"
