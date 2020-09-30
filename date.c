#include <time.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) 
{
	time_t current_time = time(NULL);
	char* token=strtok(argv[0]," ");
	token=strtok(NULL," ");
	if(token==NULL){
		struct tm *tm = localtime(&current_time);
    	//printf("\nCurrent Date and Time:\n");
    	char temp[100];
    	strftime(temp,sizeof(temp),"%a %b %d %H:%M:%S %Z %Y",tm);
    	printf("%s\n", temp);
	}
	else if(strcmp("-R",token)==0){
		struct tm *tm = localtime(&current_time);
    	//printf("\nCurrent Date and Time:\n");
    	char temp[100];
    	strftime(temp,sizeof(temp),"%a, %d %b %Y %H:%M:%S %z",tm);
    	printf("%s\n", temp);
	}
	else if(strcmp("-u",token)==0){
		struct tm *tm = gmtime(&current_time);
    	//printf("\nCurrent Date and Time:\n");
    	char temp[100];
    	strftime(temp,sizeof(temp),"%a %b %d %H:%M:%S UTC %Y",tm);
    	printf("%s\n", temp);
	}
    else if(strcmp("--help",token)==0){
        FILE *f=fopen(argv[1],"r");
        char prt[1000];
        while(fgets(prt,sizeof(prt),f))
            printf("%s",prt);
        printf("\n");
    }
    return 0;
}