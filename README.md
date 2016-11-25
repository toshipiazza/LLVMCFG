CFG Pass
========

Final project for *CSCI-4975 LLVM Compiler: A Case Study*.

## Project Outline

This project applies an LLVM pass which instruments the source code such that we can track
all conditional branches taken by an application. Potential uses include static analysis
augmentation (maliciously crafted conditional branches can confuse IDA and radare2,
etc) and branch coverage.

## Installation

```
$ cd llvm/lib/Transforms/
$ git clone https://github.com/toshipiazza/LLVMCFG.git CFG
$ echo "add_subdirectory(CFG)" >> CMakeLists.txt
```

## How to Use

``` {bash}
#!/usr/bin/env bash
# runpass.sh

# compile the CMake project
set -e
make -j LLVMCFG

# copy the branch library over
cp /path/to/cfg/libbranch/libbranch.so .

# compile the source tode into test.bc, and then run our pass on it
clang++ -g emit-llvm -c $@ -o test.bc
opt -load ./lib/LLVMCFG.so -cfg < test.bc > test-out.bc
clang++ test-out.bc -o test-out.out -L . -lbranch -pthread # our pass requires these libs
```
