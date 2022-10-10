#!/bin/sh
#task8.sh
#COSC350 Lab2 Task 8
#Shell script calculates and prints the sum of a given integers digits


#input validation
if [ $# -ne 1 ]; then
	echo "Only one argument can be passed into task8.sh!!!!"
	exit 1
fi

#store the length of the argument
argLength=$(expr length "$1");

sum=0;
num=$1;

for i in $(seq 1 $argLength);
do
	digit=$((num%10));
	sum=$(($sum+$digit));
	num=$((num/10));
done

echo "Sum of digit for number is $sum";
