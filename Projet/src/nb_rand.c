#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

        unsigned int seed = 1337;

	srand(seed);

        rand();

	
	return(EXIT_SUCCESS);
}

