#!/bin/bash

# number of threads
for threads in 1 2 4 8
do
    echo NUMT = $threads
    for attempts in 1000000 5000000 10000000 10000000
    do
        g++ -DNUMT=$threads -DNUMTRIALS=$attempts  carlo.cpp -o carlo.exe -lm -fopenmp
        ./carlo.exe
    done
done

rm carlo.exe