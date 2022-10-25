/**
 * Spencer Lefever
 * COSC350 Lab7 Task2
 *
 * ctrlc1.c program from BLP 4th Edition
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL);
}

int main()
{
	(void) signal(SIGINT, ouch);

	while(1) {
		printf("Hello world!\n");
		sleep(1);
	}
}
