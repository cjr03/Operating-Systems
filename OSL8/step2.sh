#!/bin/bash
for file in file1.txt file2.txt file3.txt file4.txt 
do
	echo "step2 $file"
	time ./step2 $file
	echo " "
done
