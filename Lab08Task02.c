#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
double arr[20];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread4(void *);

/*
Lab 8 Task 2
This program involves creating 4 threads and having them perform operations on a global array.
one thread is called first and it records 20 double entries into a global array, threads 2 and 3 both
calculate the average, minimum and maximum values, and the 4th thread clears the array. There is a pthread_join()
system call to stop the next set of threads from starting until the currently running set is finished. There is
a stop between threads 1 and 2 and 2 stops between 3 and 4 which keeps 4 from starting until 2 and 3 both finish.
*/

int main(){
    pthread_t threads[4];
    void *thret1,*thret2,*thret3;
    //create thread 1
    pthread_create(&threads[0],NULL,thread1,NULL);
    //waits until thread 1 finishes
    pthread_join(threads[0],&thret1);
    //create threads 2 and 3
    pthread_create(&threads[1],NULL,thread2,NULL);
    pthread_create(&threads[2],NULL,thread3,NULL);
    //wait until threads 2 and 3 finish
    pthread_join(threads[1],&thret2);
    pthread_join(threads[2],&thret3);
    //create thread 4
    pthread_create(&threads[3],NULL,thread4,NULL);


    pthread_exit(NULL);
    exit(0);
}

//inputs 20 entries into the array
void *thread1(void *arg){
for(int i = 0; i < 20; i++){
    double l = 0;
    printf("Input %d entry of the array: ",(i+1));
    scanf("%lf",&l);
    arr[i] = l;
}
}

//calculates average of the array
void *thread2(void *arg){
double avg = 0;
    for(int i = 0; i <  20; i++){
pthread_mutex_lock(&mutex);
avg = avg + arr[i];
pthread_mutex_unlock(&mutex);
    }
avg = avg/20;
printf("average: %lf",avg);
}

//calculates the maximum and minimum values
void *thread3(void *arg){
    double minimum = arr[0];
    double maximum = arr[0];
    for(int i = 0; i < 20; i++){
pthread_mutex_lock(&mutex);
//change to minimum and maximum values are locked.
    if(arr[i] > maximum){
        maximum = arr[i];
    }
    if(arr[i] < minimum){
        minimum = arr[i];
    }
//change to minimum and maximum values are unlocked
pthread_mutex_unlock(&mutex);
    }
    printf("\nminimum: %lf \nmaximum: %lf \n",minimum,maximum);
}

//clears the array and prints it out
void *thread4(void *arg){
for(int i = 0; i < 20; i++){
    printf("entry %d: %lf\n",i,arr[i]);
}
for(int i = 0; i < 20; i++){
    arr[i] = 0;
}
}
