#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

        unsigned int seed = 1337;

        srand(seed);

        for(int i=0; i<5; i++){
                printf("nb: %d\n", rand());
                sleep(1);
        }

        return(EXIT_SUCCESS);
}