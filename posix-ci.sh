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
  # TODO: Run tests for Linux on Travis CI once we can figure out how to talk to
  # gnome-keyring-daemon.  node-keytar hasn't figured it out either.  I think
  # that the daemon needs to be run before login to be able to unlock our login
  # keychain, but I don't see how that's possible with Travis CI.  For now, we
  # can at least check that things compile correctly.
  echo "Skipping tests until gnome-keyring-daemon works on Travis CI"
fi

# All done
cd .. || exit $?
