CFG Pass
========

Final project for *CSCI-4975 LLVM Compiler: A Case Study*.

## Project Outline

This project applies an LLVM pass which instruments the source code such that we can track
all conditional branches taken by an application. Potential uses include static analysis
augmentation (maliciously crafted conditional branches can confuse IDA and radare2 [^1],
etc) and branch coverage.

## Installation

```
$ cd llvm/lib/Transforms/
$ git clone https://github.com/toshipiazza/LLVMCFG.git CFG
$ echo "add_subdirectory(CFG)" >> CMakeLists.txt
```

[^1]: See *Practical Malware Analysis* for more information on anti-disassembly
techniques.
