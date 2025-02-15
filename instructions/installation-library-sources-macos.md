# Installation of LAL and its dependencies (Mac OS)

In this file is detailed step by step the compilation and installation process of this library and all its dependencies from sources.

## Installing the dependencies

### Compiler

We have tested LAL's compilation on MacOS with [GNU's `gcc`](https://www.gnu.org/software/gcc/) (version `11.2.0`). In order to install it on your computer, we suggest [these instructions](https://discussions.apple.com/thread/8336714), summarized in one command here:

	$ brew install gcc
	
### CMake

As it is pointed out [here](https://macappstore.org/cmake/), install `cmake` issuing the following command

	$ brew install cmake

### GMP

The [GMP](https://gmplib.org/) can be installed very easily from sources. First, [download the source files](https://gmplib.org/#DOWNLOAD) in the form of a compressed file. Uncompress it, and open a command line terminal in the new directory. There, issue the following commands

	$ CC=/usr/local/Cellar/gcc/11.2.0/bin/gcc-11 CXX=/usr/local/Cellar/gcc/11.2.0/bin/g++-11 ./configure --enable-cxx
	$ make -j4
	$ make check -j4   # GMP developers strongly recommend to run these commands, and so do we.
	$ make install

### Git

You can install [git](https://git-scm.com/) [in Mac OS](https://git-scm.com/download/mac) issuing the following command

	$ brew install git

## Compiling and installing LAL

The following commands provide an easy and quick way of downloading, compiling and installing the library. First, download LAL's sources from its [github page](https://github.com/LAL-project/linear-arrangement-library.git)

	$ git clone https://github.com/LAL-project/linear-arrangement-library.git

The following commands are used to compile the library in both `debug` and `release` builds. The `cmake` command is configured by default to install the compiled files in the `/usr` directory. In order to change this, simply specify the desired installation directory by adding this

	-DCMAKE_INSTALL_PREFIX=directory

to the `cmake` command. See below for examples.

### Release build

#### Make the build directory

	$ cd linear-arrangement-library
	$ mkdir lal-release
	$ cd lal-release

#### CMake with the predefined settings

	$ cmake -DCMAKE_CXX_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/g++-11 -DCMAKE_C_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/gcc-11 ../lal

#### CMake with other settings

	$ cmake -DCMAKE_CXX_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/g++-11 -DCMAKE_C_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/gcc-11 -DCMAKE_INSTALL_PREFIX=~/Desktop ../lal

#### Compile and install

	$ make -j4
	$ make install

### Debug build

#### Make the build directory

	$ cd linear-arrangement-library
	$ mkdir lal-debug
	$ cd lal-debug

#### CMake with the predefined settings

	$ cmake -DCMAKE_CXX_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/g++-11 -DCMAKE_C_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/gcc-11 -DCMAKE_BUILD_TYPE=Debug ../lal

#### CMake with other settings

	$ cmake -DCMAKE_CXX_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/g++-11 -DCMAKE_C_COMPILER=/usr/local/Cellar/gcc/11.2.0/bin/gcc-11 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=~/Desktop ../lal

#### Compile and install

	$ make -j4
	$ make install
