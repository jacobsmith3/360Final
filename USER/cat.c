#include "ucode.c"

char buf[1024], cwd[256], filename[1024], c[2];
int n;

int main(int argc, char *argv[])
{
    int fd, fd2, i;
    char *s;

    s = argv[1];
    if (argc == 1)   // if no path is passed
    {
        printf("Jacobs cat:\n");
        // copy stdin to stdout
        i = 0;
        strcpy(buf, ""); // make sure buf is clear
        while(n = read(0, c, 1))
        {
            if (c[0] == '\r' || c[0] == '\n') // if a return carrige or newline is encountered, print and continue
            {
                //strcat(buf, c);
                printf("\n%s\n", buf);
                strcpy(buf, "");
                continue;
            }

            write(1, c, 1);   // display incoming characters 
            
            if (c == 3) // if ^C is encountered, return
                return 0;

            if (i >= 1024)
            {
                printf("\n%s", buf);
                strcpy(buf, "");
                continue;
            }
            c[1] = '\0';
            strcat(buf, c); // append to buf so we can print everything at once
            //printf("hello\n");
            i++;
        }
    }
    else    // cat filename
    {
        strcpy(filename, argv[1]);
        printf("Jacobs cat: %s\n", filename);
        fd = open(filename, O_RDONLY);
        while (n = read(fd, buf, 1024))
        {
            for(i = 0; i < n; i++)
            {
                putc(buf[i]);
            }
            strcpy(buf, "");
        }
        close(fd);
    }
}