#include "Project.h"
int main(){
    key_t accessKey = ftok("Server",1234),accessKey2 = ftok("Server2",1234);
    int sharedMemoryId = shmget(accessKey,27,IPC_CREAT|0666);
    if(sharedMemoryId < 0) printf("Error getting shared memory");
    key_t clientsKey = ftok("Clients",1234);
    int* sharedMemory = shmat(sharedMemoryId,NULL,0);
    pid_t pid = getpid();
    Client client;
    client.id = pid;
    int clientsId = shmget(accessKey2,sizeof(ClientList),IPC_CREAT|0666);
    ClientList *list;
    list = (ClientList*)shmat(clientsId,NULL,0);
    push(list,getpid());
    PrintList(*list);
    printf("The value in the shared memory is %d\n",*sharedMemory);
    int n = 0;
    do{
        scanf("%d",&n);
        *sharedMemory = n;
        printf("Shared memory is %d\n",*sharedMemory);
    }while(n!=908);
}