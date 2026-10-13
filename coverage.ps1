$ErrorActionPreference = "Stop"
New-Item -ItemType Directory -Force build | Out-Null
Remove-Item build\*.gcda, build\*.gcno -ErrorAction SilentlyContinue

# Chỉ module cần đo mới biên dịch với --coverage
gcc --coverage -O0 -g -std=c99 -Wall -Wextra -Isrc -c src/can_signal.c -o build/can_signal.o
gcc -std=c99 -Isrc -Ivendor/unity -c test/test_can_signal.c -o build/test_can_signal.o
gcc -std=c99 -Ivendor/unity -c vendor/unity/unity.c -o build/unity.o
gcc --coverage build/can_signal.o build/test_can_signal.o build/unity.o -o build/test_cov.exe

& .\build\test_cov.exe
gcov -b -c -o build src/can_signal.c