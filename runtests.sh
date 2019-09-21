#!/bin/bash

BUILD_DIR="bin"

mkdir -p $BUILD_DIR
if [ -f $BUILD_DIR/tests ]; then rm $BUILD_DIR/tests; fi
gcc -o $BUILD_DIR/tests $(find tests -name "*.c") && $BUILD_DIR/tests
