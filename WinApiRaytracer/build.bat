
del builds\main.exe

g++ *.cpp src\*.cpp src\objects\*.cpp -o builds/main.exe -mwindows -municode -Wall -O3 -DMULTI
