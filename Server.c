#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<signal.h>
#define true 1
#define false 0
struct Tickets{
    int seatNumber,isAvailable;
    float price;
};
struct Flight{
    int id, isFull, ticketsCount;
    char* destination;
};
int main(){
    key_t accessKey = 1234;
    int sharedMemoryId = shmget(accessKey,27,IPC_CREAT|0666);
    if(sharedMemoryId < 0) printf("Error getting shared memory");
    int* sharedMemory = shmat(sharedMemoryId,NULL,0), *s;
    if(*sharedMemory == -1) printf("Error");
    s = sharedMemory;
    *s = 123;
    while(*sharedMemory != 908){
        printf("The value: %d\n",*sharedMemory);
        sleep(1);
    }
    printf("Se hizo lectura\n");
    return 0;
}