#!/bin/bash

make

echo "----------FIFO----------"
cat testInput.txt | ./3a 10 | wc -l
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./3b 10 | wc -l
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./3c 10 | wc -l
echo "----------End Second Chance----------"
echo

echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
for size in 10 50 100 250 500; do
	cat accesses.txt | ./3a $size | wc -l
done
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
for size in 10 50 100 250 500; do
	cat accesses.txt | ./3b $size | wc -l
done
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
for size in 10 50 100 250 500; do
	cat accesses.txt | ./3c $size | wc -l
done
echo

make clean
