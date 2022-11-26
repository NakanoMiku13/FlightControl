#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<signal.h>
#include<semaphore.h>
#include<sys/sem.h>
#define true 1
#define false 0
int createSemaphore(key_t semaphoreKey,int initialValue){
    int semaphoreId;
    do{
        semaphoreId = semget(semaphoreKey,1,IPC_CREAT | 0664);
        if(semaphoreId == -1) printf("Error creating semaphore...\n");
    }while(semaphoreId == -1);
    semctl(semaphoreId, 0, SETVAL,initialValue);
    return semaphoreId;
}
int createSharedMemoryId(int accessKey){
    int sharedMemoryId;
    do{
        sharedMemoryId = shmget(accessKey,27,IPC_CREAT|0666);
        if(sharedMemoryId < 0) printf("Error creating the shared memory\nTrying again...\n");
    }while(sharedMemoryId < 0);
    return sharedMemoryId;
}
int* createSharedMemory(int sharedMemoryId){
    int *sharedMemory;
    do{
        sharedMemory = shmat(sharedMemoryId,NULL,0);
        if(*sharedMemory == -1) printf("Error accessing\nTrying again...\n");
    }while(*sharedMemory == -1);
    return sharedMemory;
}
void down(int semaphoreId){
   struct sembuf op_p[]={0,-1,0};
   semop(semaphoreId,op_p,1);
}
void up(int semaphoreId){
   struct sembuf op_v[]={0,+1,0};
   semop(semaphoreId,op_v,1);
}
void clearSharedMemory(int sharedMemoryId){
    while(shmctl(sharedMemoryId,0,NULL) != 0);
}
