#include "ucode.c"
int console;

int parent(int tty0, int ttyS0, int ttyS1) // P1's code
{
    int pid, status;
    while(1){
        printf("INIT : wait for ZOMBIE child\n");
        pid = wait(&status);
        if (pid==tty0){ // if console login process died
            printf("INIT: forks a new console login\n");
            tty0 = fork(); // fork another one
            if (tty0)
                continue;
            else
                exec("login /dev/tty0"); // new console login process
        }
        if (pid==ttyS0){ // if console login process died
            printf("INIT: forks a new console login\n");
            ttyS0 = fork(); // fork another one
            if (ttyS0)
                continue;
            else
                exec("login /dev/ttyS0"); // new console login process
        }
        if (pid==ttyS1){ // if console login process died
            printf("INIT: forks a new console login\n");
            ttyS1 = fork(); // fork another one
            if (ttyS1)
                continue;
            else
                exec("login /dev/ttyS1"); // new console login process
        }

        printf("INIT: I just buried an orphan child proc %d\n", pid);
    }
}

main(){
    int tty0,ttyS0, ttyS1; // file descriptors for terminal I/O
    open("/dev/tty0", O_RDONLY); // file descriptor 0
    open("/dev/tty0", O_WRONLY); // for display to console

    printf("INIT : fork a login proc on console\n");
    printf("Jacob Smiths init\n");
    tty0 = fork();
    if (!tty0){
        exec("login /dev/tty0");
    }
    ttyS0 = fork();
    if(!ttyS0){
        exec("login /dev/ttyS0");
    }
    ttyS1 = fork();
    if(!ttyS1){
        exec("login /dev/ttyS1");
    }

    parent(tty0,ttyS0, ttyS1);
}