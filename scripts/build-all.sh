#!/usr/bin/bash

if [[ "$OSTYPE" == "msys" ]]; then
    presets=("msvc.debug" "msvc.develop" "msvc.release" "clangcl.debug" "clangcl.develop" "clangcl.release")
elif [[ "$OSTYPE" == *"gnu"* ]]; then
    presets=("clang.debug" "clang.develop" "clang.release" "gcc.debug" "gcc.develop" "gcc.release")
else
    echo "Unsupported Platform: $OSTYPE"
    exit 1
fi

for preset in "${presets[@]}"; do
    echo "Building \"$preset\""

    cmake --preset "$preset" &&
    cmake --build --preset "$preset" &&
    ctest --preset "$preset"
done
