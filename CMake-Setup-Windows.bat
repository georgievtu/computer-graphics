@echo off
color 0a
Title CG SetUp for Windows
echo CG SetUp ...
echo.
echo                    ...::::::::::::::::::::::::          ..::~~~~~~~~~~~~~~~~~~~~~~~~~~~!
echo               .~!7?JJJJYYYYYYYYYYYYYYYYYYYYYYJ7.     .:!?5GB####@@@@@@@@@@@@@@@@@@@@@@@@@@#5
echo           :~7?JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYJ!:     ?5B#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y
echo        .~?JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYJ!.    :?G#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y
echo      .!JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY?:    :Y#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y:
echo     ~JYYYYYYYYYYYYJ7!~::::::::::::::::::.    ?#@@@@@@@@@@@@#PJ7!~^^^^^^^^^^:
echo    !YYYYYYYYYYYJ!:.                          5@@@@@@@@@@@#J.                            ...
echo   !YYYYYYYYYYJ!.                            Y@@@@@@@@@@#J.        YBBBBBBBBBBBBBBBBBBBBBB#J
echo  :JYYYYYYYYYY~                             ~@@@@@@@@@@#7        5#@@@@@@@@@@@@@@@@@@@@@@@@~
echo  ~YYYYYYYYYY?.                             J@@@@@@@@@@G      .!P@@@@@@@@@@@@@@@@@@@@@@@@@@G
echo  !YYYYYYYYYYJ.                             Y@@@@@@@@@@B.    ~5#############BBB##@@@@@@@@@@?
echo  YYYYYYYYYYY7.                            7@@@@@@@@@@@5.   ................. !@@@@@@@@@@#:
echo  .7YYYYYYYYYYYJ!..                        .G@@@@@@@@@@@#J~:                  Y@@@@@@@@@@P
echo   .?YYYYYYYYYYYYYJ??7777777777777777777~    :G@@@@@@@@@@@@@#BGP555555555555555#@@@@@@@@@@!
echo    .!JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY!    .J#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B.
echo      .!?YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY7.    :JB@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@J
echo        .:~7JJYYYYYYYYYYYYYYYYYYYYYYYYYYYYYJ!.    .~JP##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
echo            .:~~!7777777777777777777777777777.      .!7JY5PPPPPPPPPPPPPPPPPPPPPPPPPPPY 
echo.
:ask_choice
set /p choice="Do you want to use CMake or Premake? (C/P): "
if /i "%choice%"=="C" (
    echo You chose CMake.
    rem Delete the premake folder and all its contents
    if exist premake (
        rmdir /s /q premake
        echo premake folder deleted.
    ) else (
        echo premake folder not found.
    )
    rem delete the premake5.lua file
    if exist premake5.lua (
        del premake5.lua
        echo premake5.lua deleted.
    ) else (
        echo premake5.lua not found.
    )
    rem delete the Premake-Linux.sh and Premake-Windows.bat files
    if exist Premake-Linux.sh (
        del Premake-Linux.sh
        echo Premake-Linux.sh deleted.
    ) else (
        echo Premake-Linux.sh not found.
    )
    if exist Premake-Windows.bat (
        del Premake-Windows.bat
        echo Premake-Windows.bat deleted.
    ) else (
        echo Premake-Windows.bat not found.
    )
    rem Delete the dependencies folder and all its contents
    if exist dependencies (
        rmdir /s /q dependencies
        echo dependencies folder deleted.
    ) else (
        echo dependencies folder not found.
    )
    rem make build folder and go to it
    if not exist build mkdir build
    cd build
    rem run cmake
    cmake ..
    cd ..
) else if /i "%choice%"=="P" (
    echo You chose Premake.
    rem Delete the CMakeLists.txt file from the current folder
    if exist CMakeLists.txt (
        del CMakeLists.txt
        echo CMakeLists.txt deleted.
    ) else (
        echo CMakeLists.txt not found.
    )
    rem delete the lib folder and all its contents
    if exist lib (
        rmdir /s /q lib
        echo lib folder deleted.
    ) else (
        echo lib folder not found.
    )
    rem delete the src/CMakeLists.txt file
    if exist src\CMakeLists.txt (
        del src\CMakeLists.txt
        echo src\CMakeLists.txt deleted.
    ) else (
        echo src\CMakeLists.txt not found.
    )
    rem delete the and the Premake-Linux.sh files
    if exist Premake-Linux.sh (
        del Premake-Linux.sh
        echo Premake-Linux.sh deleted.
    ) else (
        echo Premake-Linux.sh not found.
    )
    call premake\premake5.exe vs2022
) else (
    echo Invalid choice. Please enter C for CMake or P for Premake.
    goto ask_choice
)
if exist CG_SetUpW.bat (
    del CG_SetUpW.bat
    echo CG_SetUpW.bat deleted.
) else (
    echo CG_SetUpW.bat not found.
)
if exist CG_SetUpLM.sh (
    del CG_SetUpLM.sh
    echo CG_SetUpLM.sh deleted.
) else (
    echo CG_SetUpLM.sh not found.
)
echo.
PAUSE
color 07
cls
