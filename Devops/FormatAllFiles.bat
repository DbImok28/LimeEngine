@echo off
CD ..\
FOR /R %%f IN (*.cpp, *.hpp, *.h) DO (
    echo %%f
    clang-format -i %%f
)
PAUSE