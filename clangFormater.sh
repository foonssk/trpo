#!/bin/bash

files=$(find . -name "*.cpp")

for file in $files; do
    clang-format -i $file
done