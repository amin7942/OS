#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char* arvg[]){
	int SIZE = 4096;
	char *name = arvg[1];
	printf("%s\n", name);
	int shm_fd;
	char *ptr;
	char input[100];

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);

	ptr = (char*) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	printf("Welcome to my remote shell client!\n");
	printf("Connected to server vla Shared memory.\n");
	
	while(1){
		fgets(input, 100, stdin);
		input[strlen(input)-1]='\0';
		sprintf(ptr, "%s", input);
		//ptr += strlen(input);
	}
	return 0;
}
