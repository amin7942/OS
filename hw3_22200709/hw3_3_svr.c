#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

char** split(char* str, char* delim, int* count) {
	char* temp = strdup(str);
	char* token = strtok(temp, delim);
	char** result = NULL;
	*count = 0;

	while(token != NULL){
		result = realloc(result, sizeof(char*)*(*count + 1));
		result[*count] = strdup(token);
		(*count)++;
		token = strtok(NULL, delim);
	}
	result[*count] = NULL;
	free(temp);
	return result;
}

int main(int argc, char* argv[]){
	if(argc > 2) {
		printf("wrong parameter\n");
		return 0;
	}
	printf("Welcome to  my remote shell server!\n");

	int SIZE = 512;
	char* name = argv[1];
	char command[SIZE];
	
	int shm_fd;
	char* ptr = NULL;

	shm_fd = shm_open(name, O_RDWR, 0666);
	if(shm_fd == -1){
		perror("shm_open error");
	}


	printf("Wating for a command...\n");
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(ptr == MAP_FAILED){
		perror("mmap");
	
	}
	//char temp[50];
	char str[50];
	int exe_error = 0;
	
	while(1){
		//while(str[strlen(str)-1] == '\n');
		//while(strlen(str) == 0);

		while(strcmp(str, ptr) == 0);

		strcpy(str, ptr);

		char** cmd;
		int count;
		if(strcmp(ptr, "exit_svr") == 0) {
			printf("Bye!\n");
			break;
		}
		pid_t pid = fork();

		if(pid < 0){
			fprintf(stderr, "fork failed\n");
		}else if(pid == 0){
			//printf("%s\n", (char*)ptr);
			//if(strcmp(ptr, str) != 0){
				//ptr[strlen(ptr)-1] = '\0';	
			cmd = split(str, " ", &count);
			exe_error = execvp(cmd[0], cmd);
			
			//}

			if(exe_error == -1){
				perror("execvp failed\n");
			}
		}else{
			int status;
			wait(&status);
			if(status != 0) printf("what the hack\n");
			//while(strcmp(str, ptr) == 0){
				//usleep(100000);
			//};
		}
		//str[0] = '\0';
		usleep(100000);
	}
	shm_unlink(name);

	return 0;
}
