#!/bin/bash
# Script for testing husky

echo "Running Random Generator" 
cd Tests/Input
clang++ -std=c++14 generator.cpp
./a.out
echo "Running Husky Test"
cd ../Husky 
clang++ -std=c++14 HuskyTest.cpp
./a.out
echo "Running FTL Test"
cd ../FTL
clang++ -std=c++14 ftlTest.cpp
./a.out
#echo "Running FC++"
#cd ../Fcpp
#clang++ -std=c++14 fcppTest.cpp
#./a.out
echo "Running Python Test"
cd ../Python
python3 pythonTest.py
echo "Running Haskell Test"
cd ../Haskell
ghc haskellTest.hs
./haskellTest
