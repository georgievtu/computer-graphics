# computer-graphics

# Template Project for CG Labs

_Work in progress_

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

### After the first build when you make changes to the source code:

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

you don't need to run cmake again after the first build.

## Linux setup

Unlike Windows and MacOs, Linux does not come with most of the tools. You need to install them manually.

1.  On Ubuntu(or other Debian-based distros), you can install the following packages:
    ```sh
    sudo apt-get update
    sudo apt-get upgrade

    sudo apt-get install git
    sudo apt install build-essential
    sudo apt install cmake
    sudo apt install pkg-config

    // Optional for OpenGL (may not be needed)
    sudo apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
    sudo apt-get install libglew-dev libglfw3-dev libglm-dev
    sudo apt-get install libao-dev libmpg123-dev
    sudo apt install libxinerama
    sudo apt install libxinerama-dev
    sudo apt-get install libxcursor-dev
    sudo apt-get install libxi-dev
    ```

2. On other distros, you are on your own :) . You can search for the equivalent packages for your distro.

## MacOs setup

1. Install Xcode from the App Store.
2. Install Homebrew from [here](https://brew.sh/).
3. Install the following packages using Homebrew:
   ```sh
   brew install git
   brew install cmake
   ```

## Windows setup

1. Install Visual Studio Code from [here](https://code.visualstudio.com/).
2. Install the C/C++ Extension Pack from the Extensions tab in Visual Studio Code.
3. Install CMake from [here](https://cmake.org/download/).
4. Install Git from [here](https://git-scm.com/download/win).
5. (Optional if you want more then MSVC for compiler) Install MinGW from [here](https://sourceforge.net/projects/mingw/). Add the MinGW bin directory to the system PATH.

## Done

After installing the required packages, you can follow the steps mentioned above to build the project.