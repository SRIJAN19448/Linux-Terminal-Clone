#include <stdio.h> 
#include <dirent.h> 
#include <errno.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
	char input1[1000];
	char input[1000];
    char * token=strtok(argv[0]," ");
    token=strtok(NULL," ");
    if(token==NULL){
    	printf("cat: provide atleast 1 file");
    }
    else if(strcmp("-n",token)==0){
    	token=strtok(NULL," ");
    	if(token==NULL){
    		printf("cat: provide atleast 1 file");
    	}
    	else{
    		int count=1;
    		int flag=0;
    		while(token!=NULL){
				strcpy(input1,token);
				FILE *f;
				f=fopen(input1,"r");
				if(f==NULL){
					printf("cat: ");
					printf("%s: ",input1);
					printf("%s\n",strerror(errno));
				}
				else{
					while(fgets(input,sizeof(input),f)!=NULL){
						if(flag==0){
							printf("\t%d ",count);
							count++;
						}
						else
							flag=0;
						
						printf("%s",input);
					
					}
					flag=1;
				}
				token=strtok(NULL," ");
			}
    	}
    }
    else if(strcmp("-b",token)==0){
    	token=strtok(NULL," ");
    	if(token==NULL){
    		printf("cat: provide atleast 1 file");
    	}
    	else{
    		int count=1;
    		int flag=0;
    		while(token!=NULL){
				strcpy(input1,token);
				FILE *f;
				f=fopen(input1,"r");
				if(f==NULL){
					printf("cat: ");
					printf("%s: ",input1);
					printf("%s\n",strerror(errno));
				}
				else{
					while(fgets(input,sizeof(input),f)!=NULL){
						if(flag==0 && strcmp(input,"\n")==0){
							printf("%s",input);
						}
						else if(flag==0){
							printf("\t%d ",count);
							count++;
							printf("%s",input);
						}
						else{
							flag=0;
							printf("%s",input);
						}
					}
					flag=1;
				}
				token=strtok(NULL," ");
			}
    	}
    }
    else if(strcmp("--help",token)==0){
    	FILE *f=fopen(argv[1],"r");
    	char prt[1000];
    	while(fgets(prt,sizeof(prt),f))
    		printf("%s",prt);
    	printf("\n");
    }
    else{
		while(token!=NULL){
			strcpy(input1,token);
			FILE *f;
			f=fopen(input1,"r");
			if(f==NULL){
				printf("cat: ");
				printf("%s: ",input1);
				printf("%s\n",strerror(errno));
			}
			else{
				while(fgets(input,sizeof(input),f)!=NULL){
				printf("%s",input);
				}
			}
			token=strtok(NULL," ");
		}
	}
	exit(0);
}