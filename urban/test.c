#include <stdio.h>
#include <stdint.h>

uint8_t regex(char *str,char* pattern);

int main(int argc, char *argv[]){
	
	if (argc <3)
		return 0;
	char *str = argv[1];
	char *pattern = argv[2];

	printf("%d\n",argc);

	printf("MATCHED:%d\n",regex(str,pattern));
	
	return 0;
	}
