/**
 * Spencer Lefever
 * COSC350 lab6 task1
 *
 * Write a getenv() function called mygetenv()
 *
 * Main method tests the getenv() function
 *
 * Allows for env to be passed in as command line argument
 * or env can be manually types into program
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char** environ;

char* mygetenv(const char*);

int main(int argc, char** argv) {
	if(argc < 2)
		printf("mygetenv() returns: %s\n",mygetenv("TERM"));

	if(argc==2)
		printf("mygetenv() returns: %s\n", mygetenv(argv[1]);

}



//Function returns the value of the enviromental variable name
char* mygetenv(const char* name) {
	char** env = environ;

	while(*env != NULL) {

		if(bcmp(name, *env, sizeof(*name)) == 0){
			return *env;
		}
		*env++;
	}
}


