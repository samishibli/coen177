#!/bin/bash 
echo "Running Lab 2 Step 1"
echo " "
./1.c  
echo "Step 1 Completed"
sleep 5
echo " "
echo "Running Lab 2 Step 3 with delay 500"
echo " "
./3.c 500
sleep 5
echo " "
echo "Running Lab 2 Step 3 with delay 5000"
echo " "
./3.c 5000
echo "Step 3 Completed"
sleep 5
echo " "
echo "Running Lab 2 Step 5"
echo " "
./5.c 4000 400 40 40000
echo "Step 5 Completed"
sleep 10
echo " "
echo "Running Lab 2 Step 6"
echo " "
./6.c 4000 400 40 40000 5000
echo "Step 6 Completed"
sleep 6
echo " "
echo "Running Lab 2 Step 7"
echo " "
./7.c  
echo "Step 7 Completed"
sleep 10
echo " "
echo "Running Lab 2 Step 8"
echo " "
./8.c 4000
echo "Step 8 Completed"
