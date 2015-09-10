#!/bin/sh

# Common CI test script for POSIX systems (OS X and others)

# Create build directory and move there
mkdir build || exit $?
cd build || exit $?

# Run configuration
cmake -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE} .. || exit $?

# Build
cmake --build . || exit $?

# Test
ctest --output-on-failure || exit $?

# All done
cd .. || exit $?
