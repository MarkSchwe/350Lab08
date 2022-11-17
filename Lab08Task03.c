#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/*
Lab 8 Task 3
This program creates an infinite loop where an input is read from STDIN using a parent process
and that input is sent to a child process using a pipe. This is similar to a program discussed
in class involving the same concept (that being sending inputs into a pipe to be added together 
and printed out in a child process).
*/

int main()
{
int i, pip[2], size, i1, i2;
pid_t pid;
char line1[50], line2[50];
//pipe is created
pipe(pip);
    //fork is called to create a child process.
pid = fork();
if (pid > 0) //parent process
{
    //reading side is closed.
    close(pip[0]); 
    printf("submit two integers\n");
    while ((size = read(1, line1, 20)) > 0)
    {
        //line taken from keyboard input goes into the writing side of the pipe
        write(pip[1], line1, size);
        printf("submit two integers\n");
    }
}
 else //child process
{
    //writing side is closed
    close(pip[1]);
    //keeps going while parent is still sending input to child using the reading side of the pipe
    while ((i = read(pip[0], line2, 20))>0) 
    {
        //input is changed from char type to int and analyzed to make sure both inputs are integer types. (both return 1)
    if (sscanf(line2, "%d%d", &i1, &i2) == 2)
    {
        //sum is recorded into line2 using sprintf
    sprintf(line2, "%d\n", i1 + i2);
    i = strlen(line2); //n becomes length of line2 for the sake of write()
    //line2 (sum) is output to screen at size n
    if (write(1, line2, i) != i){
        printf("write error");
    }
    } else {
        //output if input is not 2 integers
    if (write(1, "invalid argument\n", 17) != 17){
        printf("write error");
    }
    }
}
}
exit(0);
}
