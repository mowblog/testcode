@echo off
rem if "%computername%"=="oncebye" goto oncebye else goto jma-test

rem :oncebye
rem call "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86

rem :jma-test
call "H:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86

del *.exe
del *.obj

cl /MT /Fetcpc.exe tcpc.cpp mysock.cpp
cl /MT /Fetcps.exe tcps.cpp mysock.cpp
cl /MT /Feudpc.exe udpc.cpp mysock.cpp
cl /MT /Feudps.exe udps.cpp mysock.cpp

del *.obj

pause