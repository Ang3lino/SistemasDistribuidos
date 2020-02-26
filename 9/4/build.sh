#!/bin/bash

g++ 4.cpp library.cpp -pthread
fname='out4.txt'

rm $fname
touch $fname
for i in {1..7}; do
    echo "Ejecutando $i"
    result=$(time ./a.out $i > /dev/null)
    echo $result >> $fname
done


