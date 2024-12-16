#!/bin/bash
echo "----------Running Make----------"
make all
echo "----------Listing Files----------"
ls -l file?.txt
echo "----------Running Steps----------"
echo "Step 2"
for file in file1.txt file2.txt file3.txt file4.txt
do
    echo "step2 $file"
    /usr/bin/time -p ./step2 $file
done
echo "Step 3"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
	echo "step3 $file $buffer"
        /usr/bin/time -p ./step3 $file $buffer
    done
done
echo "Step 4"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
	echo "step4 $file $buffer"
        /usr/bin/time -p ./step4 $file $buffer
    done
done
echo "Step 5"
for file in file1.txt file2.txt file3.txt file4.txt
do
    for buffer in 100 1000 10000 100000
    do
        for thread in 2 8 32 64
        do
	    echo "step5 $file $buffer $thread"
            /usr/bin/time -p ./step5 $file $buffer $thread
        done
    done
done
make clean
