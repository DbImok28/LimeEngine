:: Copyright (C) Pavel Jakushik - All rights reserved
:: See the LICENSE file for copyright and licensing details.
:: GitHub: https://github.com/RubyCircle/LimeEngine

@echo off
CD ..\LimeEngine\Engine
FOR /R %%f IN (*.cpp, *.hpp, *.h) DO (
    echo %%f
    clang-format -i %%f
)
PAUSE