# computer-graphics

# Template Project for CG Labs

_Work in progress_

## How to configure the project

### If you choose Premake Configuration
#### Windows (Visual Studio only)
1. Navigate to the root directory of the project 
    
    Run 
    ```sh
    .\CG_SetUpW.bat
    ```
    ##### OR 
    double click on `CG_SetUpW.bat` 


2. When prompted, select the Premake (by typing 'p' or 'P' and pressing Enter)

3. Open the generated Visual Studio solution file `ComputerGraphics.sln` in Visual Studio

4. Build and run the project

#### Linux
1. Navigate to the root directory of the project
2. Run 
    ```sh
    .\Premake-Linux.sh
    ```
3. When prompted, select the Premake (by typing 'p' or 'P' and pressing Enter)
4. Build the project by running make
    ```sh
    make
    ```
5. Run the project
    ```sh
    ./src/Debug/CG
    ```
### If you choose CMake Configuration
#### Windows (preferably Visual Studio Code) 
1. Navigate to the root directory of the project
2. Run 
    ```sh
    .\CG_SetUpW.bat
    ```
3. When prompted, select the CMake (by typing 'c' or 'C' and pressing Enter)
4. Open the project in Visual Studio Code
5. Configure the project using CMake Tools extension
- From the command palette (Ctrl+Shift+P), select `CMake: Configure`
- Select the build system (e.g. `Visual Studio 16 2019`)
- Build the project by selecting `CMake: Build`
- Run the project by selecting `CMake: Run`

#### Linux
1. Navigate to the root directory of the project
2. Run 
    ```sh
    sudo chmod +x CG_SetUpLM.sh
    ```
3. Run 
    ```sh
    ./CG_SetUpLM.sh
    ```
4. When prompted, select the CMake (by typing 'c' or 'C' and pressing Enter)
5. Build and Run the project
    ```sh
    cd build
    make
    cd ..
    ./build/src/Project
    ```
6. (optional) you can also use Visual Studio Code to build and run the project
    - Open the project in Visual Studio Code
    - Configure the project using CMake Tools extension (Ctrl+Shift+P -> CMake: Configure)
    - Build the project (Ctrl+Shift+P -> CMake: Build)
    - Run the project (Ctrl+Shift+P -> CMake: Run)

#### MacOS
1. Navigate to the root directory of the project
2. Run 
    ```sh
    chmod +x CG_SetUpLM.sh
    ```
3. Run 
    ```sh
    ./CG_SetUpLM.sh
    ```
4. When prompted, select the CMake (by typing 'c' or 'C' and pressing Enter)
5. Build and Run the project using Visual Studio Code
    - Open the project in Visual Studio Code
    - Configure the project using CMake Tools extension (Ctrl+Shift+P -> CMake: Configure)
    - Build the project (Ctrl+Shift+P -> CMake: Build)
    - Run the project (Ctrl+Shift+P -> CMake: Run)

## How to Build the Project Using Premake

Just run one of the following script files based on your operating system:

- `Premake-Windows.bat` for Windows
- `Premake-Linux.sh` for Linux and MacOS

## How to Build the Project Using CMake

The best and easiest way to build this project is to use Visual Studio Code along with the C/C++ Extension Pack. Follow the instructions provided in the extension pack documentation to set up your environment and build the project.

## How to Build the Project Manually Using CMake

If you prefer to build the project manually using CMake, follow these steps:

1. Make sure you have CMake installed on your system.
2. Create a build directory in the root of the project:
    ```sh
    mkdir build
    ```
3. Navigate to the build directory:
    ```sh
    cd build
    ```
4. Run CMake to configure the project:
    ```sh
    cmake ..
    ```
5. Run make to build the project:
    ```sh
    make
    ```
6. Run the project:
    ```sh
    ./src/Project
    ```

### After the First Build When You Make Changes to the Source Code

1. Navigate to the build directory:
    ```sh
    cd build
    ```
2. Run make to build the project:
    ```sh
    make
    ```
3. Run the project:
    ```sh
    ./src/Project
    ```

You don't need to run CMake again after the first build.

## Linux Setup

Unlike Windows and MacOS, Linux does not come with most of the tools. You need to install them manually.

1. On Ubuntu (or other Debian-based distros), you can install the following packages:
     ```sh
     sudo apt-get update
     sudo apt-get upgrade

     sudo apt-get install git
     sudo apt install build-essential
     sudo apt install cmake
     sudo apt install pkg-config

     # Optional for OpenGL (may not be needed)
     sudo apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
     sudo apt-get install libglew-dev libglfw3-dev libglm-dev
     sudo apt-get install libao-dev libmpg123-dev
     sudo apt install libxinerama
     sudo apt install libxinerama-dev
     sudo apt-get install libxcursor-dev
     sudo apt-get install libxi-dev
     ```

2. On other distros, you are on your own. You can search for the equivalent packages for your distro.

## MacOS Setup

1. Install Xcode from the App Store.
2. Install Homebrew from [here](https://brew.sh/).
3. Install the following packages using Homebrew:
    ```sh
    brew install git
    brew install cmake
    ```

## Windows Setup

1. Install Visual Studio Code from [here](https://code.visualstudio.com/).
2. Install the C/C++ Extension Pack from the Extensions tab in Visual Studio Code.
3. Install CMake from [here](https://cmake.org/download/).
4. Install Git from [here](https://git-scm.com/download/win).
5. (Optional if you want more than MSVC for compiler) Install MinGW from [here](https://sourceforge.net/projects/mingw/). Add the MinGW bin directory to the system PATH.

## Done

After installing the required packages, you can follow the steps mentioned above to build the project.
