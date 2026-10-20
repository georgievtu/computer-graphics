# Computer Graphics

Template project for computer graphics labs for TU Sofia.\
This project is intended for **educational purposes** and does not represent best practices in regards to renderer architecture or C++/OpenGL usage.

## Requirements

- GPU driver support for **OpenGL 3.3** (4.6 recommended)
- Git

## Download

1. Create a folder.
2. Open a terminal in your folder.
3. Run:
    ```sh
    git clone https://github.com/georgievtu/computer-graphics
    ```

## Build

Supports Premake and CMake:
- Premake works with Visual Studio and GNU Make. **No additional downloads required**.
- CMake works with Visual Studio Code (*CMake Tools extension recommended*). **CMake must be [installed](https://cmake.org/download/) seperately. A C/C++ compiler must also be installed and set on the system path. [Python](https://www.python.org/downloads/) is required to fetch the dependencies.**

**(OPTIONAL)** Run `CMakeSetup-Windows.bat` OR `CMakeSetup-LinuxAndMac.sh` and select your desired build system.

### Premake

#### Windows (Visual Studio)
1. Download Visual Studio.
2. Choose "Desktop development with C++" during installation.
3. Run `Premake-Windows.bat` (double click)
4. Open the generated `ComputerGraphics.sln` file in Visual Studio.

#### Linux (GNU Make)
1. Download the GNU build tools package with your package manager. Example for Debian:
    ```sh
    sudo apt install build-essential
    ```
2. Make the premake script executable:
    ```sh
    chmod +x Premake-Linux.sh
    ```
3. Run the premake script:
    ```sh
    ./Premake-Linux.sh
    ```
4. Build using make:
    ```sh
    make -j12
    ```
5. Run:
    ```sh
    ./bin/Debug/CG
    ```

#### MacOS (Make)

**Note**: The default build is configured to generate ARM64 code for Apple Silicon. For Intel Macs, edit the architecture in the `lua` files.

1. Install a C/C++ compiler.\
 **(RECOMMENDED)** Clang from Xcode command tools:
    ```sh
    % xcode-select --install 
    ```
2. Make the premake script executable:
    ```sh
    chmod +x Premake-Mac.sh
    ```
3. Run the premake script:
    ```sh
    ./Premake-Mac.sh
    ```
    **(IMPORTANT)** The premake script calls the `premake/premake5-mac` binary.\
    It may be flagged as unverified and refuse to run on some machines.\
    To allow it to execute run:
    ```sh
    xattr -d com.apple.quarantine premake/premake5-mac
    ```
    If you do not trust the provided binary, download Premake from [here](https://premake.github.io/).

4. Build using make:
    ```sh
    make -j12
    ```
5. Run:
    ```sh
    ./bin/Debug/CG
    ```

<a name="cmake">

### Cmake

#### MacOS

1. Install Xcode from the App Store.
2. Install Homebrew from [here](https://brew.sh/).
3. Install CMake using Homebrew:
    ```sh
    brew install cmake
    ```

#### Visual Studio Code (All platforms)

- **Requires CMake and a compiler installed and set on path**
1. Install Visual Studio Code from [here](https://code.visualstudio.com/).
2. Install the C/C++ Extension Pack from the Extensions tab in Visual Studio Code.
3. Open the project in Visual Studio Code.
4. Configure the project using CMake Tools extension (Ctrl+Shift+P -> CMake: Configure).
5. Build the project (Ctrl+Shift+P -> CMake: Build).
6. Run the project (Ctrl+Shift+P -> CMake: Run).

### Troubleshooting

If you get an OpenGL unsupported version error, downgrade the version info defined in `cg::version` and in the shaders located in `resources/shaders` to the highest available for your graphics driver. The minimum supported version is 3.3. On Mac, the version is automatically downgraded to 4.1.

## Exercises

The exercises are located in the `labs` folder.

## License

This project is licensed under the MIT License. All dependencies fall under their respective licenses. For more information see their corresponding license in the `dependencies` folder.

## Credits
[Vladimir Kucev](https://github.com/savety6) - For the CMake build.
