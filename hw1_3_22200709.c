#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Word{
	char str[100];
	int start;
	int end;
};

int main(){
	printf("input a text: ");
	char s[100];
	struct Word w[100];
	fgets(s, 100, stdin);
	s[strlen(s)-1] = '\0';
	w[0].start = 0;

	int blank[100];
	memset(blank, 0, 100);
	char temp[100];
	int t = 0, j = 0, i = 0, b = 0;
	int flag = 0;

	for(; i < strlen(s); i++, t++){
		if(s[i] != ' ' && s[i] != 9 && s[i] != '\n') {
			if(flag == 1) {
				w[j].start = i;
				b++;
			}
			temp[t] = s[i];
			flag = 0;
		}

		if(s[i] == ' ' || s[i] ==  9 || s[i] == '\n'){
			if(s[i] == ' ') blank[b]++;
			if(s[i] == 9) blank[b]+=6;
			
			if(flag == 1) {
				t = - 1;
				continue;
			}
			flag = 1;
			w[j].end = i;
			for(int k = 0; k < t; k++){
            	w[j].str[k] = temp[k];
        	}
			t = -1;

			j++;
				
			w[j].start = i+1;
		}
	}
	for(int k = 0; k < t; k++){
   		 w[j].str[k] = temp[k];
    }
	w[j].end = i;

	for(int i = 0; i < 14; i++){
		printf(" ");
	}

	for(int i = 0; i <= j; i++){
		printf("[");

		for(int h = w[i].start; h < w[i].end - 1; h++)
			printf(" ");

		printf("]");
		if(i < j){
			for(int h = 0; h < blank[i]-1; h++){
				printf(" ");
			}
		}
			
		
	}
	printf("\n");
	for(int i = 0; i <= j; i++){
		printf("words[%d] = (%d, %d, %s)\n", i, w[i].start, w[i].end, w[i].str);
	}
	return 0;
}
