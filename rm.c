#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
int checking(int ch,int v,char* name){
    if (ch==0 & v==1) {
        printf("rm: removed file ");
        printf("%s\n",name);
        return 0;
    }
    else if(ch==0)
        return 0;
    else { 
    	printf("rm: ");
    	printf("%s: ",name);
    	printf("%s\n",strerror(errno));
        // if(errno==EACCES){
        //     printf("rm: cannont remove file ");
        //     printf("%s",name);
        //     printf(": permission denied\n"); 
        // }
        // else if(errno==EISDIR){
        //     printf("rm: cannot remove file ");
        //     printf("%s",name);
        //     printf(": filename refers to directory\n");
        // }
        // else{
        //     printf("rm: cannot remove file ");
        //     printf("%s",name);
        //     printf(": unrecognised error while removing file\n");
        // }
        return 1;
    } 
}
int main(int argc, char** argv){
	int exit_val=0;
	char* token=strtok(argv[0]," ");
	token=strtok(NULL," ");
	if(token==NULL){
		printf("rm: provide a filename\n");
	}
	else if(strcmp("-v",token)==0){
		token=strtok(NULL," ");
		if(token==NULL){
			printf("rm: provide a filename\n");
		}
		else{
			while(token!=NULL){
				int check=unlink(token);
				int temp=checking(check,1,token);
				if(exit_val==0 && temp==1)
					exit_val=1;
				token=strtok(NULL," ");
			}
		}
	}
	else if(strcmp("-i",token)==0){
		token=strtok(NULL," ");
		if(token==NULL){
			printf("rm: provide a filename\n");
		}
		else{
			while(token!=NULL){
				char choice;
				printf("rm: remove file ");
				printf("%s ? ",token);
				scanf("%c",&choice);
				if(choice=='\n')
					scanf("%c",&choice);
				if(choice=='y'){
					int check=unlink(token);
					int temp=checking(check,0,token);
					if(exit_val==0 && temp==1)
						exit_val=1;
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
			int check=unlink(token);
			int temp=checking(check,0,token);
			if(exit_val==0 && temp==1)
				exit_val=1;
			token=strtok(NULL," ");
		}
	}
	exit(exit_val);
}