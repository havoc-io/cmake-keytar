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
if [ "$TRAVIS_OS_NAME" = "osx" ]; then
  ctest --output-on-failure || exit $?
else
  # HACK: Have to use a virtual X11 environment for GNOME code
  xvfb ctest --output-on-failure || exit $?
fi

# All done
cd .. || exit $?
