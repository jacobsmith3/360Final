#include "ucode.c"
// tried to done redirects but couldnt get it to work properly

int forkexec(char* comline, int* w){
    int pid = fork();
    if(pid==0){
        runcommand(comline);
    }
    else{
        pid = wait(&w);
        return pid;
    }
}

int runcommand(char* comline){
    char cp[64], cat[64];
    strcpy(cp,"");
    for (int i = strlen(comline)-1; i >= 0; --i){
        if (comline[i] == '>'){
            if(strcmp(cp,"")==0){
                return -1;
            }
            else{
                printf("Hello\n\n");
                close(1);
                open(cp+1,1);
                strcpy(cp,"");
            }
        }
        else if (comline[i] == '<'){
            if(strcmp(cp,"")==0){
                return -1;
            }
            else{
                close(0);
                open(cp+1,0);
                strcpy(cp,"");
            }
        }
        else{
            cat[0] = comline[i];
            cat[1] = '\0';
            strcat(cat,cp);
            strcpy(cp,cat);
            strcpy(cat,"");
        }
    }
    exec(cp);
    return 1;
}

int main(int argc, int argv[]){
    int pid, i=0;
    int w;
    char tty[16], comline[64];
    while(1){
        printf("\nJacob sh:");
        gets(comline);
        if(strcmp(comline, "")==0){
            continue;
        }
        if(strcmp(comline,"cd")==0){
            for (; comline[i] != ' '; i++){}
            chdir(comline+i);
        }
        if(strcmp(comline, "logout") == 0){
            uexit();
        }
        if(strcmp(comline,"exit")==0){
            uexit();
        }
        forkexec(comline, w);

        close(0);
        close(1);
        gettty(tty);
        open(tty,O_RDONLY);
        open(tty,O_WRONLY);
    }
}