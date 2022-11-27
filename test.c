#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<signal.h>
#include<semaphore.h>
#include<sys/msg.h>
int createSharedMemoryId(int accessKey){
    int sharedMemoryId;
    int* arr = (int*)malloc(sizeof(int)*250);
    do{
        sharedMemoryId = shmget(accessKey,sizeof(arr),IPC_CREAT|0666);
        if(sharedMemoryId < 0) printf("Error creating the shared memory\nTrying again...\n");
    }while(sharedMemoryId < 0);
    return sharedMemoryId;
}
int* createSharedMemory(int sharedMemoryId){
    int *sharedMemory;
    do{
        sharedMemory = shmat(sharedMemoryId,0,0);
        if(*sharedMemory == -1) printf("Error accessing\nTrying again...\n");
    }while(*sharedMemory == -1);
    return sharedMemory;
}
int main(){
   int* arr = createSharedMemory(createSharedMemoryId((key_t)ftok("sys",1234)));
   for(int i = 0;i<10;i++){
      scanf("%d",&arr[i]);
   }
}