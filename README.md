MPEI Algebraic Abstractions Library
=====

AAL is a C++ library, which supports the theoretical and practical study of the properties and algorithms for finite groups, fields, and cryptographic systems and protocols based on these algebraic structures. It supports a wide range of algebraic structures and allows to perform calculations in the interactive mode, and through the development and research programs on the basis of it. Designed for use in performing laboratory works, course and diploma projects, undergraduate and graduate works, as well as to demonstrate the algebraic aspects of the studied discipline.

Usage
------------

To bulid a library on Windows use one of the projects from Dev_project directory. You can build python bindings using CMake and SWIG. On Unix you will run:

    cd Bindings
    cmake -i .
    make
    ./aaltest.exe

Enabling USE_MIRACL and USE_MSIEVE while configuring will let you download and build all dependecies. Note, default setting (without dependencies) won't give you fully functional binding.
