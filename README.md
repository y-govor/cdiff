# cdiff

A simple console utility for calculating the difference between two files written in C++.

## Building

### Supported OS

The application has been tested on Windows and Linux, but it should also work on other POSIX-compliant operating systems, such as macOS and FreeBSD.

### Supported compilers

The following compilers are recommended for building the project: GCC, Clang and MinGW. While Microsoft Visual C++ is also supported, Makefile for building with MSVC is not provided.

For users who want to build the project with MSVC, there are two options available:
1. Create a new C++ project in Visual Studio and add all files from `src` folder (recommended).
2. Write a Makefile specifically for MSVC (advanced).

### Step-by-step instructions

1. Install the necessary tools

The following examples show how to install GCC and make on a few popular Linux distributions.

- Debian, Ubuntu

    ```
    sudo apt update
    sudo apt install build-essential
    ```

- Fedora

    ```
    sudo dnf update
    sudo dnf install make automake gcc gcc-c++
    ```

- Arch Linux

    ```
    sudo pacman -Syu
    sudo pacman -S base-devel
    ```

[MinGW](https://www.mingw-w64.org/) is needed to build C and C++ projects on Windows. The official website has numerous versions for various systems.

[winlibs.com](https://winlibs.com/) hosts standalone builds for Windows, as well as installation instructions. Building the project on Windows systems was tested with the following flavor of MinGW:
- Win32 - i686 (32-bit)
- Threading library: POSIX
- Runtime library: MSVCRT

2. Clone the repository:

    ```
    git clone https://github.com/y-govor/cdiff.git
    cd cdiff
    ```

3. Create the `bin` directory:

    ```
    mkdir bin
    ```

4. Use make utility to build the project:

    ```
    make
    ```

To compile with Clang instead of GCC, open the [Makefile](Makefile) and replace the line `CXX = g++` with `CXX = clang++`. Alternatively, specify the value for `CXX` variable in the command:
```
make CXX=clang++
```

> Note for MinGW users: you might need to use `mingw32-make` instead of `make`.

## Usage

```
Usage: cdiff [options] [files]

Description:
  Compare two files and display the difference.

Options:
  -h, --help                    Display this help message and exit.
  -c, --color                   Enable color support when printing to console.
  -a, --force-ansi              Use ANSI escape codes for colors on Windows systems.
  -o, --out-file FILE           Redirect output to the file instead of a console.
  -n, --lines NUM               Number of lines for context (3 by default).

Files:
  original                      Original file.
  modified                      New (modified) file.

Examples:
  cdiff original.txt modified.txt
  cdiff -c -a original.txt modified.txt
  cdiff -o output.diff -n 5 original.txt modified.txt
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.