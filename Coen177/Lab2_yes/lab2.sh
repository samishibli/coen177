#!/bin/bash

echo "-----Part 1-----"
gcc lab2_1.c
./a.out

echo "-----Part 3-----"
gcc lab2_3.c
./a.out 3000

echo "-----Part 5-----"
gcc lab2_5.c
./a.out 300 3000 5000 50000

echo "-----Part 6-----"
gcc lab2_6.c
./a.out 300 3000 5000 5500 50000

echo "-----Part 7-----"
gcc lab2_7.c
./a.out

echo "-----Part 8-----"
gcc lab2_8.c -lpthread
./a.out 3000