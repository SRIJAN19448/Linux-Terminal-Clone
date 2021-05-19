#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>
void internal_help(char*base,char*help){
	char lhdir[1000];
	strcpy(lhdir,base);
	strcat(lhdir,help);
	FILE *f=fopen(lhdir,"r");
    char prt[1000];
    while(fgets(prt,sizeof(prt),f))
    	printf("%s",prt);
    printf("\n");
}
int call_external(char*fullcom,char*com,char*help,char*base){
	int status;
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("error\n");
	}
	else if(pid==0){
		char ldir[1000]="";
		char lhdir[1000]="";
		strcpy(ldir,base);
		strcat(ldir,com);
		strcpy(lhdir,base);
		strcat(lhdir,help);
		execlp(ldir,fullcom,lhdir,NULL);
	}
	else{
		waitpid(pid,&status,0);
	}
}
int main(){
	system("clear");
	FILE *history;
	char pdir[1000];
	getcwd(pdir,sizeof(pdir));
	char hdir[1000];
	strcpy(hdir,pdir);
	strcat(hdir,"/history.txt");

	while(1){

		int status;
		char input[1000]="";
		char inp[1000]="";
		char input1[1000]="";
		history=fopen(hdir,"a+");
		printf("SHELL:-$");
		fgets(input,sizeof(input),stdin);
		fprintf(history,"%s",input);
		strcpy(input,strtok(input,"\n"));
		strcpy(inp,input);
		char * token=strtok(input," ");
		strcpy(input1,token);

		if(strcmp(input1,"echo")==0){
			token=strtok(NULL," ");
			strcpy(input1,token);
			if(token==NULL){
				printf("echo: missing operand\n");
			}
			else if(strcmp(input1,"-n")==0){
				token=strtok(NULL," ");
				strcpy(input1,token);
				token=strtok(NULL," ");
				while(token!=NULL){
					strcat(input1," ");
					strcat(input1,token);
					token=strtok(NULL," ");
				}
				printf("%s",input1);
			}
			else if(strcmp(input1,"-E")==0){
				token=strtok(NULL," ");
				if(token==NULL){
					printf("echo: missing operand\n");
				}
				else{
					strcpy(input1,token);
					token=strtok(NULL," ");
					while(token!=NULL){
						strcat(input1," ");
						strcat(input1,token);
						token=strtok(NULL," ");
					}
				printf("%s\n",input1);
				}	
			}
			else if(strcmp("--help",token)==0)
				internal_help(pdir,"/echohelp.txt");
			else{
				token=strtok(NULL," ");
				while(token!=NULL){
					strcat(input1," ");
					strcat(input1,token);
					token=strtok(NULL," ");
				}
				printf("%s\n",input1);
			}
		}
		else if(strcmp(input1,"cd")==0){
			token=strtok(NULL," ");
			strcpy(input1,token);
			int x;
			if(token==NULL){
				printf("cd: provide a directory");
			}
			else if(strcmp("-P",token)==0){
				token=strtok(NULL," ");
				if(token==NULL){
					printf("cd: provide a directory");
				}
				else{
					x=chdir(input1);
					if(x==-1){
						if(errno==EACCES)
						{
							printf("cd: access denied\n");
						}
						else if(errno==ENOENT){
							printf("cd: path doesn't exit\n");
						}
						else{
							printf("cd: unrecognized error");
						}
					}
				}
			}
			else if(strcmp("--help",token)==0){
				internal_help(pdir,"/cdhelp.txt");
			}
			else{
				x=chdir(input1);
				if(x==-1){
					if(errno==EACCES)
					{
						printf("cd: access denied\n");
					}
					else if(errno==ENOENT){
						printf("cd: path doesn't exit\n");
					}
					else{
						printf("cd: unrecognized error");
					}
				}
			}
		}
		else if(strcmp(input1,"pwd")==0){
			char d[1000];
			token=strtok(NULL," ");
			if(token==NULL || strcmp("-P",token)==0){
				if(getcwd(d,sizeof(d))==NULL){
					if(errno==ENOENT){
						printf("pwd: the present working directory has been unlinked.\n");
					}
					else if(errno==ENOMEM){
						printf("pwd: out of memory.");
					}
					else{
						printf("pwd: unrecognized error");
					}
				}
				else{
					printf("%s\n",d);
				}
			}
			else if(strcmp("--help",token)==0){
				internal_help(pdir,"/pwdhelp.txt");
			}
		}
		else if(strcmp(input1,"history")==0){
			token=strtok(NULL," ");
			if(token==NULL){
				fseek(history,0,SEEK_SET);
				while(fgets(input,sizeof(input),history)!=NULL){
					printf("%s",input);
				}
			}
			else if(strcmp("-c",token)==0){
				fclose(history);
				history=fopen("history.txt","w");
			}
			else if(strcmp("-w",token)==0){
				token=strtok(NULL," ");
				if(token==NULL){
					printf("history: provide a filename\n");
				}
				else{
					
					FILE *fil=fopen(token,"r+");
					if(fil==NULL){
						printf("history: unable to open file\n");
					}
					else{
						fseek(history,0,SEEK_SET);
						fseek(fil,0,SEEK_END);
						while(fgets(input,sizeof(input),history)!=NULL){
							fprintf(fil,"%s",input);
						}
						fclose(fil);
					}
				}
			}
			else if(strcmp("--help",token)==0){
				internal_help(pdir,"/historyhelp.txt");
			}
		}
		else if(strcmp(input1,"exit")==0){
			fclose(history);
			token=strtok(NULL," ");
			if(token==NULL)
				exit(0);
			else if(strcmp("--help",token)==0)
				internal_help(pdir,"/exithelp.txt");
			else
				exit(atoi(token));
		}
		else if(strcmp(input1,"ls")==0)
			call_external(inp,"/ls.out","/lshelp.txt",pdir);
		
		else if(strcmp(input1,"cat")==0)
			call_external(inp,"/cat.out","/cathelp.txt",pdir);

		else if(strcmp(input1,"date")==0)
			call_external(inp,"/date.out","/datehelp.txt",pdir);

		else if(strcmp(input1,"mkdir")==0)
			call_external(inp,"/mkdir.out","/mkdirhelp.txt",pdir);
		
		else if(strcmp(input1,"rm")==0)
			call_external(inp,"/rm.out","/rmhelp.txt",pdir);
		
		else if(strcmp(input1,"clear")==0)
			system("clear");
		fclose(history);
	}

}
