#!/bin/sh
#task6b.sh
#Spencer Lefever
#COSC350 Lab2 Task 6b
#Shell script to make a left arrow based on user input of base and tail

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

	numSpace=$(($baseSize-($i*2)));
	#Print spaces
	for j in $(seq 1 $numSpace);
	do
		printf " ";
	done

	#Calculate number of "*" to print
	numPrint=$((($i*2)-1));

	for k in $(seq 1 $numPrint);
	do
		printf "*";
	done
	
	printf "\n";

done

#Holds side of base and tail for printing middle
midSize=$((baseSize+tailSize));

#Make middle of arrow with tail

for i in $(seq 1 $midSize);
do
	printf "*";
done

printf "\n";

#Make second half of arrow
for i in $(seq 1 $halfBase);
do
	numSpace=$(((i*2)-1));
	#Print spaces
	for j in $(seq 1 $numSpace);
	do
		printf " ";
	done

	#Calc number of "*" to print
	numPrint=$(($baseSize-($i*2)));

	for k in $(seq 1 $numPrint);
	do
		printf "*";
	done

	printf "\n";

done
