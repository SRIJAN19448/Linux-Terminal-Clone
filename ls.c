#include <stdio.h> 
#include <dirent.h> 
#include <errno.h>
#include <stdlib.h>
#include <string.h>
int main(int arrgc, char **argv) 
{ 
    char *token=strtok(argv[0]," ");
    token=strtok(NULL," ");
    if(token==NULL){
        DIR *dr=opendir(".");
        if(dr==NULL){
            printf("ls: ");
            printf("%s\n",strerror(errno));
        }
        else{
            struct dirent *de;
            while ((de = readdir(dr)) != NULL) 
                if(strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0)
                    printf("%s\n", de->d_name);
        }
        closedir(dr);
    }
    else if(strcmp("-A",token)==0)
    {
        token=strtok(NULL," ");
        DIR *dr;
        if(token==NULL){
            dr=opendir(".");
        }
        else{
            dr=opendir(token);
        }

        if(dr==NULL){
            printf("ls: ");
            printf("%s\n",strerror(errno));
        }
        else{
            struct dirent *de;
            while ((de = readdir(dr)) != NULL) 
                if(strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0)
                    printf("%s\n", de->d_name); 
        }
        closedir(dr);
    }
    else if(strcmp("-a",token)==0)
    {
        token=strtok(NULL," ");
        DIR *dr;
        if(token==NULL){
            dr=opendir(".");
        }
        else{
            dr=opendir(token);
        }

        if(dr==NULL){
            printf("ls: ");
            printf("%s\n",strerror(errno));
        }
        else{
            struct dirent *de;
            while ((de = readdir(dr)) != NULL) 
                printf("%s\n", de->d_name); 
        }
        closedir(dr);
    }
    else if(strcmp("--help",token)==0){
    	FILE *f=fopen(argv[1],"r");
    	char prt[1000];
    	while(fgets(prt,sizeof(prt),f))
    		printf("%s",prt);
    	printf("\n");
    }  
    else{
        DIR *dr;
        dr=opendir(token);
        if(dr==NULL){
            printf("ls: ");
            printf("%s\n",strerror(errno));
        }
        else{
            struct dirent *de;
            while ((de = readdir(dr)) != NULL) 
                if(strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0)
                    printf("%s\n", de->d_name); 
        }
    }
    exit(0);
} 
