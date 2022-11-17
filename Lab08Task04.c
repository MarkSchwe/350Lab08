#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Lab 8 Task 4
This program outputs a command through a command line by using popen. Very similar to a program discussed in 
class except instead of having a set output it takes command line input in order to execute a command.
*/

int main(int argc, char **argv)
{
//line for output
char line[256];
//line for command line input
char test[200] = "";
//loop to concatinate every command line input into one so it can be used in popen
for(int i = 1; i < argc; i++){
    sprintf(test, "%s %s",test,argv[i]);
}
//file for popen
FILE *fil;
//opens output file associated with the command the test string asks for
fil = popen(test, "r");
//infinite loop
while(1) 
{
    //gets each line of the file
if (fgets(line, 256, fil) == NULL){
    break;
}
//output is flushed for new line
fflush(stdout);
//output is sent to stdout
fputs(line, stdout);
}
printf("\n");
//file is closed
pclose(fil);
exit(0);
}
