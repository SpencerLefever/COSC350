#!/bin/sh
#task6a.sh
#Spencer Lefever
#COSC350 Lab2 Task 6a
#Shell script to make a diamond based on user input of size

echo "Enter an odd number"
read num
oddCheck=$((num%2))
halfNum=$((num/2))


#input validation
if [ $oddCheck -eq 0 ]; then
	echo "Number entered must be odd!!!"
	exit 1
fi

if [ $num -lt 3 ]; then
	echo "Number must be greater than 3!!!"
	exit 1
fi

#Makes first half of diamond
for i in $(seq 1 $halfNum);
do
	#prints preceding spaces
	for j in $(seq $i $halfNum);
	do
		printf " ";
	done

	#calculates number of "*" to print
	numPrint=$((($i*2)-1));

	for k in $(seq 1 $numPrint);
	do
		printf "*";
	done

	printf "\n";

done

#Makes middle part of diamond
for i in $(seq 1 $num);
do
	printf "*";
done

printf "\n";

#makes second half of diamond
for i in $(seq 1 $halfNum);
do
	#prints preceding spaces
	for j in $(seq 1 $i);
	do
		printf " ";
	done

	#calculates number of "*" to print
	numPrint=$(($num-($i*2)));

	for k in $(seq 1 $numPrint);
	do
		printf "*";
	done
	
	printf "\n";
done
