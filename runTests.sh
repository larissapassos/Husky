#!/bin/bash
# Script for testing husky

clang++ -std=c++14 ./Tests/Input/generator.cpp
./Tests/Input/a.out
clang++ -std=c++14 ./Tests/Husky/HuskyTest.cpp
./Tests/Husky/a.out
clang++ -std=c++14 ./Tests/FTL/ftlTest.cpp
./Tests/FTL/a.out
clang++ -std=c++14 ./Tests/Fcpp/fcppTest.cpp
./Tests/Fcpp/a.out
python3 ./Tests/Python/pythonTest
ghc ./Tests/Haskell/haskellTest.hs
./Tests/Haskell/haskellTest