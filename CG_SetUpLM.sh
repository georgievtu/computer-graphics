#!/bin/bash
clear
echo -e "\e[32mCG SetUp for Linux\e[0m"
echo

echo "CG SetUp ..."
echo
echo "                    ...::::::::::::::::::::::::          ..::~~~~~~~~~~~~~~~~~~~~~~~~~~~!"
echo "               .~!7?JJJJYYYYYYYYYYYYYYYYYYYYYYJ7.     .:!?5GB####@@@@@@@@@@@@@@@@@@@@@@@@@@#5"
echo "           :~7?JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYJ!:     ?5B#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y"
echo "        .~?JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYJ!.    :?G#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y"
echo "      .!JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY?:    :Y#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y:"
echo "     ~JYYYYYYYYYYYYJ7!~::::::::::::::::::.    ?#@@@@@@@@@@@@#PJ7!~^^^^^^^^^^:"
echo "    !YYYYYYYYYYYJ!:.                          5@@@@@@@@@@@#J.                            ..."
echo "   !YYYYYYYYYYJ!.                            Y@@@@@@@@@@#J.        YBBBBBBBBBBBBBBBBBBBBBB#J"
echo "  :JYYYYYYYYYY~                             ~@@@@@@@@@@#7        5#@@@@@@@@@@@@@@@@@@@@@@@@~"
echo "  ~YYYYYYYYYY?.                             J@@@@@@@@@@G      .!P@@@@@@@@@@@@@@@@@@@@@@@@@@G"
echo "  !YYYYYYYYYYJ.                             Y@@@@@@@@@@B.    ~5#############BBB##@@@@@@@@@@?"
echo "  YYYYYYYYYYY7.                            7@@@@@@@@@@@5.   ................. !@@@@@@@@@@#:"
echo "  .7YYYYYYYYYYYJ!..                        .G@@@@@@@@@@@#J~:                  Y@@@@@@@@@@P"
echo "   .?YYYYYYYYYYYYYJ??7777777777777777777~    :G@@@@@@@@@@@@@#BGP555555555555555#@@@@@@@@@@!"
echo "    .!JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY!    .J#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B."
echo "      .!?YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY7.    :JB@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@J"
echo "        .:~7JJYYYYYYYYYYYYYYYYYYYYYYYYYYYYYJ!.    .~JP##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "            .:~~!7777777777777777777777777777.      .!7JY5PPPPPPPPPPPPPPPPPPPPPPPPPPPY "
echo

ask_choice() {
    read -p "Do you want to use CMake or Premake? (C/P): " choice
    case "${choice^^}" in
        C)
            echo "You chose CMake."
            # Delete the premake folder and all its contents
            if [ -d "premake" ]; then
                rm -rf premake
                echo "premake folder deleted."
            else
                echo "premake folder not found."
            fi

            # Delete the premake5.lua file
            if [ -f "premake5.lua" ]; then
                rm premake5.lua
                echo "premake5.lua deleted."
            else
                echo "premake5.lua not found."
            fi

            if [ -f "Premake-Linux.sh" ]; then
                rm Premake-Linux.sh
                echo "Premake-Linux.sh deleted."
            else
                echo "Premake-Linux.sh not found."
            fi

            if [ -f "Premake-Windows.bat" ]; then
                rm Premake-Windows.bat
                echo "Premake-Windows.bat deleted."
            else
                echo "Premake-Windows.bat not found."
            fi

            # Delete the dependencies folder and all its contents
            if [ -d "dependencies" ]; then
                rm -rf dependencies
                echo "dependencies folder deleted."
            else
                echo "dependencies folder not found."
            fi

            # Create build folder if not exists, go into it, run CMake
            [ ! -d "build" ] && mkdir build
            cd build
            cmake ..
            cd ..
            ;;
        P)
            echo "You chose Premake."
            
            # Delete CMakeLists.txt from the current folder
            if [ -f "CMakeLists.txt" ]; then
                rm CMakeLists.txt
                echo "CMakeLists.txt deleted."
            else
                echo "CMakeLists.txt not found."
            fi

            # Delete the lib folder and all its contents
            if [ -d "lib" ]; then
                rm -rf lib
                echo "lib folder deleted."
            else
                echo "lib folder not found."
            fi

            # Delete src/CMakeLists.txt
            if [ -f "src/CMakeLists.txt" ]; then
                rm src/CMakeLists.txt
                echo "src/CMakeLists.txt deleted."
            else
                echo "src/CMakeLists.txt not found."
            fi

            if [ -f "Premake-Linux.sh" ]; then
                rm Premake-Linux.sh
                echo "Premake-Linux.sh deleted."
            else
                echo "Premake-Linux.sh not found."
            fi

            premake/premake5-linux gmake2
            ;;
        *)
            echo "Invalid choice. Please enter C for CMake or P for Premake."
            ask_choice
            ;;
    esac

    # Delete the setup and related files
    if [ -f "CG_SetUpW.bat" ]; then
        rm CG_SetUpW.bat
        echo "CG_SetUpW.bat deleted."
    else
        echo "CG_SetUpW.bat not found."
    fi

    #Delete The CG_SetUpLM.sh
    if [ -f "CG_SetUpLM.sh" ]; then
        rm CG_SetUpLM.sh
        echo "CG_SetUpLM.sh deleted."
    else
        echo "CG_SetUpLM.sh not found."
    fi

}

ask_choice