#!/bin/sh
#task6c.sh
#Spencer Lefever
#COSC350 Lab2 Task 6c
#Shell script to make a right arrow based on user input of base and tai;

   
echo "Enter a base (MUST BE ODD)"
read baseSize

oddCheck=$((baseSize%2))
halfBase=$((baseSize/2))

#base input validation
if [ $baseSize -eq 0 ]; then
	echo "Number entered must be odd!!!"
	exit 1
fi

#read in tail if base is odd
echo "Enter a tail"
read tailSize

#Make first half of arrow
for i in $(seq 1 $halfBase);
do
	#Print Spaces
	for j in $(seq 1 $tailSize);
	do
		printf " ";
	done

	#Calc number of "*" to print
	numPrint=$((($i*2)-1));

	#Print "*"
	for k in $(seq 1 $numPrint);
	do
		printf "*";
	done

	printf "\n";

done

#holds the size of the base and tail
midSize=$((baseSize+tailSize));

#print middle with tail
for i in $(seq 1 $midSize);
do
	printf "*";
done

printf "\n";

#Make second half of arrow
for i in $(seq 1 $halfBase);
do
	#print spaces
	for j in $(seq 1 $tailSize);
	do
		printf " ";
	done

	#Calc number of "*" to print
	numPrint=$(($baseSize-(i*2)));
	for k in $(seq 1 $numPrint);
	do
		printf "*";
	done

	printf "\n";
	
done
