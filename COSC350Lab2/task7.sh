#!/bin/sh
#task7.sh
#Spencer Lefever
#COSC350 Lab2 task 7
#Shell script takes in integer arguments and calculates factorial

echo "Enter an integer"
read num
factorial=1;

for i in $(seq 1 $num);
do
	factorial=$(($factorial*$i));
done

echo $factorial;
