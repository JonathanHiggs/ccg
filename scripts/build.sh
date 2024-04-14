#!/usr/bin/bash

preset="$1"
test -z "$preset" && echo "Missing preset" && exit 1

cmake --preset "$preset" &&
cmake --build --preset "$preset" &&
ctest --preset "$preset"
