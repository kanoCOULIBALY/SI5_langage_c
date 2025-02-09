#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv []){

	char cmdArg[100];
	char cmd[200] = "/usr/bin/ssh_original ";

	for(int i=1; i<argc; i++){
		strcat(cmdArg, argv[i]);
		if((i+1) < argc){
			strcat(cmdArg, " ");
		}
	}
	
	strcat(cmd, cmdArg);
	system(cmd);

	printf("%s\n",cmdArg);
	
	return 0;
}
