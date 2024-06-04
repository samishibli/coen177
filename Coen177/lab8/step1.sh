#!/bin/bash
# 100K (100,000 bytes)
cat /dev/urandom | head -c 100000 > file1.txt
# 1M (1,000,000 bytes)
cat /dev/urandom | head -c 1000000 > file2.txt

# 10M (10,000,000 bytes)
cat /dev/urandom | head -c 10000000 > file3.txt

# 100M (100,000,000 bytes)
cat /dev/urandom | head -c 100000000 > file4.txt

# Verify the sizes of the created files
ls -la file1.txt file2.txt file3.txt file4.txt
