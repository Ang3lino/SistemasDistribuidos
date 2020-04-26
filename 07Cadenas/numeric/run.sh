#!/bin/sh

g++ a.cpp
echo 'C++'
echo "$(time ./a.out)"

javac A.java 
echo 'Java'
echo "$(time java A)"

echo 'Python 3'
echo "$(time python3 a.py)"