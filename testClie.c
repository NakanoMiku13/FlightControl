#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
int main(){
    key_t accessKey = 1234;
    int sharedMemoryId = shmget(accessKey,27,IPC_CREAT|0666);
    if(sharedMemoryId < 0) printf("Error getting shared memory");
    int* sharedMemory = shmat(sharedMemoryId,NULL,0), *s;
    printf("The value in the shared memory is %d\n",*sharedMemory);
    int n = 0;
    do{
        scanf("%d",&n);
        *sharedMemory = n;
        printf("Shared memory is %d\n",*sharedMemory);
    }while(n!=908);
}