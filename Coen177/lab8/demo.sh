#!/bin/bash

echo "----------Running Make----------"
make all
echo "----------Listing Files----------"
ls -l file?.txt
echo "----------Running Steps----------"

echo "-----------------Step 2-------------------------"
for file in file1.txt file2.txt file3.txt file4.txt
do
    echo "Running step2 on $file"
    /usr/bin/time -p ./step2 $file
done

echo "-----------------Step 3-------------------------"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        echo "Running step3 on $file with buffer size $buffer"
        /usr/bin/time -p ./step3 $file $buffer
    done
done

echo "-----------------Step 4-------------------------"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        echo "Running step4 on $file with buffer size $buffer"
        /usr/bin/time -p ./step4 $file $buffer
    done
done

echo "-----------------Step 5-------------------------"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        for thread in 2 8 32 64
        do
            echo "Running step5 on $file with buffer size $buffer and $thread threads"
            /usr/bin/time -p ./step5 $file $buffer $thread
        done
    done
done

make clean
