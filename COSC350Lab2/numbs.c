/*
 * Spencer Lefever 
 * COSC350 Lab2
 * C program to write ints 1-100 to a file
 */

#include<stdio.h>

int main(){
	FILE *fptr;
	fptr = fopen("numbs", "w");

	for(int i=1; i<=100; i++) {
		fprintf(fptr, "%d\n", i);
	}
	fclose(fptr);
	return 0;
}
