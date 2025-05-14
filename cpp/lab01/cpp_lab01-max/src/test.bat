@echo off
setlocal enabledelayedexpansion

echo Compiling the program...
g++ -std=c++17 -o wc.exe wc.cpp
if not exist wc.exe (
    echo Compiling error
    exit /b 1
)

echo Creating test files...

echo. > empty.txt
echo Hello world!> simple.txt
echo Line1^&echo Line2> multiline.txt
echo     > spaces.txt
echo Special!@#%%^&*()>> special_chars.txt

set TEST_CASE=1

echo [Test !TEST_CASE!] Test of an empty file [wc.exe empty.txt]
wc.exe empty.txt
set /a TEST_CASE+=1

echo.&echo [Test !TEST_CASE!] Test of a simple file [wc.exe simple.txt]
wc.exe simple.txt
set /a TEST_CASE+=1

echo.&echo [Test !TEST_CASE!] Test of multiple files [wc.exe simple.txt multiline.txt]
wc.exe simple.txt multiline.txt
set /a TEST_CASE+=1

echo.&echo [Test !TEST_CASE!] -l -w -c options [wc.exe -l -w -c simple.txt]
wc.exe -l -w -c simple.txt
set /a TEST_CASE+=1

echo.&echo [Test !TEST_CASE!] Groupped options -lwc [wc.exe -lwc multiline.txt]
wc.exe -lwc multiline.txt
set /a TEST_CASE+=1

echo.&echo [Test !TEST_CASE!] Special chars [wc.exe --chars special_chars.txt]
wc.exe --chars special_chars.txt
set /a TEST_CASE+=1

echo.&echo [Test !TEST_CASE!] Test of a non-existent file [wc.exe not_exist.txt]
wc.exe not_exist.txt
set /a TEST_CASE+=1

echo.&echo Clearing temp files...
del empty.txt simple.txt multiline.txt spaces.txt special_chars.txt

echo.&echo All test cases completed!
pause