#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *sumnum(void *);
void *facto(void *);

/*
Lab 8 Task 1:
This program creates two threads and has them both calculate the sum and factorial of a command line input
using mutex in order to make sure neither thread causes any problems for the other while it works.
*/

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Invalid arguments.\n");
        exit(-1);
    }
pthread_t threads[2];
int num = 0;
num = atoi(argv[1]);
printf("In main: creating thread 1\n");
//first thread is created
pthread_create(&threads[0], NULL, sumnum, (void *)num);
printf("In main: creating thread 2\n");
//second thread is created
pthread_create(&threads[1], NULL, facto, (void *)num);
pthread_exit(NULL);
exit (0);
}

//function that is tied with thread 2
void *facto(void *num){
    int fact = 1;
int n = (int)num;
for (int i =0; i<n; i++)
{
    //change to factorial value is locked so nothing goes wrong
pthread_mutex_lock(&mutex);
fact = fact * (i+1);
    //change to factorial value is finished for this loop so value is unlocked.
pthread_mutex_unlock(&mutex);
}
//factorial total is printed
printf("factorial total: %d\n",fact);
pthread_exit(NULL);
}

//function that is tied with thread 1
void *sumnum(void *num)
{
    int sum = 0;
int n = (int)num;
for (int i =0; i<n; i++)
{
    //change to sum value is locked so nothing goes wrong
pthread_mutex_lock(&mutex);
sum = sum + (i+1);
    //change to sum value is finished for this loop so value is unlocked.
pthread_mutex_unlock(&mutex);
}
//sum total is printed
printf("sum total: %d \n",sum);
pthread_exit(NULL);
}
