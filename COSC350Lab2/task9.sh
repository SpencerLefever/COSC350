#!/bin/sh
#task9.sh
#Spencer Lefever
#COSC350 Lab2 task 9
#Shell script search for a word in a file based on user input

echo "Enter the directory the file is located under"
read dname

#Input validation for directory
if [ -d $dname ]; then
	echo "The directory $dname exists!";
else
	echo "Error: there is no such directory: $dname";
	exit 1;
fi

#Ask user for file name
for i in $(seq 1 3);
do
	echo "Enter the name of the file in $dname";
	read fname
	
	if [ -f $fname ]; then

		if [ -r $fname ]; then
			#Ask for word in file
			echo "Enter a word to find in the file";
			read word;
			
			#Search for word in file
			wordSearch=$(grep $word "$dname/$fname");

			if [ -n "$wordSearch" ]; then
				echo "$word FOUND!";
				exit 0;
			else
				echo "$word NOT FOUND";
				exit 4;
			fi

		else
			echo "Error: the file $dname/$fname exists but is not readable";
			exit 3;
		fi
	else
		echo "Error: the file $dname/$fname does not exist";
	fi
done

#If for loop is executed completely the only case 
#left to handle is the file not being found
echo "Error: file could not be located after three attempts";
exit 2;
