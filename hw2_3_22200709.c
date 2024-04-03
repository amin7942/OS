#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){
	struct stat sb;
	char buffer[20];
	if(argc != 3) {
		printf("cant execute\n");
		return 0;
	}
	if(stat(argv[1], &sb) == -1){
		perror("stat");
		return 0;
	}
	
	ssize_t write_file;
	int dest_fp = open(argv[2], O_WRONLY);
	if(dest_fp == -1){
		perror("not exist destFile");
		return 0;
	}
	snprintf(buffer, sizeof(buffer), "%ld", (long)sb.st_dev);
	char start_message[100] = {"attributes of file \""};
	strcat(start_message, argv[2]);
	strcat(start_message, "\"\n");

	write_file = write(dest_fp, start_message, strlen(start_message));
	char buffer2[100] = {"st_dev = "};

	strcat(buffer2, buffer);
	strcat(buffer2, "\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));

	strcpy(buffer2, "st_mode = ");
	snprintf(buffer, sizeof(buffer), "%ld", (long)sb.st_mode);
	strcat(buffer2, buffer);
	strcat(buffer2, "\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));

	strcpy(buffer2, "st_uid = ");
	snprintf(buffer, sizeof(buffer), "%ld", (long)sb.st_uid);
	strcat(buffer2, buffer);
	strcat(buffer2, "\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));

	
	strcpy(buffer2, "st_gid = ");
	snprintf(buffer, sizeof(buffer), "%ld", (long)sb.st_gid);
	strcat(buffer2, buffer);
	strcat(buffer2, "\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));

	strcpy(buffer2, "st_size = ");
	snprintf(buffer, sizeof(buffer), "%ld", (long)sb.st_size);
	strcat(buffer2, buffer);
	strcat(buffer2, "\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));
	
	strcpy(buffer2, "st_mtime = ");
	snprintf(buffer, sizeof(buffer), "%lld", (long long)sb.st_mtime);
	strcat(buffer2, buffer);
	strcat(buffer2, "\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));

	strcpy(buffer2, "modified time = ");
	struct tm* time_info = localtime(&sb.st_mtime);
	char time_str[30];

	strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M:%S", time_info);
	strcat(buffer2, time_str);
	strcat(buffer2, "\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));

	strcpy(buffer2, "File attributes were successfully copied.\n");
	write_file = write(dest_fp, buffer2, strlen(buffer2));

	//sszie_t write_file;
	//if(dest_fp == -1) {
		//perror("destfile error");
		//return 0;
	//}
	//while(write_file = write(dest_fp, 




	return 0;	
}
