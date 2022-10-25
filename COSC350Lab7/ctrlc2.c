/**
 * Spencer Lefever
 * COSC350 Lab7 Task2
 *
 * ctrlc2.c from BLP 4th edition
 * Modified to behave the same as ctrlc1.c
 */

/**
 * To kill the program
 * 	kill -9 <pid>
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
}


int main()
{

	struct sigaction act;
	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	

	sigaction(SIGINT, &act, 0);

	while(1) {
		printf("Hello World!\n");
		sleep(1);
	}
}
