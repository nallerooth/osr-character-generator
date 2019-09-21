#!/bin/bash

BUILD_DIR="bin"
SOURCE_FILES=$(find . -name "*.c" | grep -v "src/main.c")

mkdir -p $BUILD_DIR
if [ -f $BUILD_DIR/tests ]; then rm $BUILD_DIR/tests; fi
gcc -o $BUILD_DIR/tests $SOURCE_FILES && $BUILD_DIR/tests

