#include "Project.h"
struct Tickets{
    int seatNumber,isAvailable;
    float price;
};
struct Flight{
    int id, isFull, ticketsCount;
    char* destination;
};
int main(){
    key_t accessKey = ftok("Server",1234),accessKey2 = ftok("Server2",1234);
    sem_t semaphore;
    int sharedMemoryId = createSharedMemoryId(accessKey), *clients = createSharedMemory(sharedMemoryId);
    *clients = 0;
    int clientsId = shmget(accessKey2,10*sizeof(ClientList),IPC_CREAT|0666);
    ClientList *list;
    list = (ClientList*)shmat(clientsId,NULL,0);
    ctr(list);
    do{
        if(list->size == 0) printf("There is no client yet\n");
        else{
            printf("%d\n",list->head->id);
        }
        PrintList(*list);
        sleep(1);
    }while(*clients != 908);
    // createSemaphore(&semaphore);
    // int a = semGetValue(&semaphore);
    // int count = *clients;
    // do{
    //     if(count != *clients){
    //         printf("A new client log in...\n");
    //     }
    //     if(*clients == 0){
    //         printf("No clients...\n");
    //     }
    // }while(TRUE);
    // clearSharedMemory(sharedMemoryId);
    return 0;
}