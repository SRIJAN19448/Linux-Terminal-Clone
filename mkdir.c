
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
int checking(int ch,int v,char* name){
    if (ch==0 & v==1) {
        printf("mkdir: created directory ");
        printf("%s\n",name);
        return 0;
    }
    else if(ch==0)
        return 0;
    else if(errno==EEXIST && v==2)
        return 0;
    else{
            printf("mkdir: ");
            printf("%s: ",name);
            printf("%s\n",strerror(errno));
            return 1;
        }
}
int main(int argc, char**argv) 
{ 
    int exit_val=0;
    int check; 
    char*token=strtok(argv[0]," ");
    token=strtok(NULL," ");
    if(token==NULL){
        printf("mkdir:missing operand\n");
    }
    else if(strcmp("-v",token)==0){
        token=strtok(NULL," ");
        if(token==NULL){
            printf("mkdir:missing operand\n");
        }
        else{
            while(token!=NULL){
                check=mkdir(token,0777);
                int temp=checking(check,1,token);
                 if(exit_val==0 & temp==1)
                    exit_val=1;
                token=strtok(NULL," ");
            }
        }
    }
    else if(strcmp("-p",token)==0){
        token=strtok(NULL,"/");
        if(token==NULL){
            printf("mkdir:missing operand\n");
        }
        else{
            while(token!=NULL){
                check=mkdir(token,0777);
                int temp=checking(check,2,token);
                if(temp==1)
                    exit(1);
                chdir(token);
                token=strtok(NULL,"/");
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
            check=mkdir(token,0777);
            int temp=checking(check,0,token);
            if(exit_val==0 & temp==1)
                exit_val=1;
            token=strtok(NULL," ");
        }
    }
    exit(exit_val);
} 