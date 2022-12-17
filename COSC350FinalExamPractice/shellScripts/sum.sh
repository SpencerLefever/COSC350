#!/bin/bash

for input in $@ 
do
	sum=`expr $sum + $input`
done
echo "Sum: $sum"