#include "ucode.c"

int main(int argc, char *argv[])
{
    int fd, n, m, i;
    char buf[1024], filename[256], c[1];
    printf("Jacobs more:\n");
    if (argc == 1)  // no filename passed
    {
        while(n = read(0, c, 1))
        {
            if (c[0] == '\r' || c[0] == '\n')
            {
                putc('\n');
                continue;
            } 
            write(1, c, 1);   // display incoming characters    
        }
    }

    else
    {
        strcpy(filename, argv[1]);
        fd = open(filename, O_RDONLY);  // open file for read
        printf("\n");
        int j =0;
        int q = 0;
        i = 0;
        while(n = read(fd, buf, 1024))  // read 1024 bytes into buffer at a time
        {
            if(j == 0){
                printf("%s", buf + i);
                j=1;
            }
            else{
                for(i = 0; m = read(0, c, 1); i++)  // read stdin for next instruction. Unlike cat, no need to print this to screen
                {
                    if (c[0] == ' ')    // if space is pressed, print the rest of the buffer
                    {
                        printf("%s", buf + i);
                        break;  // read next 1024 bytes
                    }
                    if (c[0] == '\r' || c[0] == '\n')   // if enter is pressed, print the line
                    {
                        for (; buf[i] != '\r' && buf[i] != '\n'; i++)
                        {
                            putc(buf[i]);
                            if(i >= n)
                                break;
                        }
                        putc('\n');
                    }
                    else    // any other key prints the next character
                    {
                        putc(buf[i]);
                    }
                    if (i >= n)
                        break;                
                }            
            }
        }
    }
}