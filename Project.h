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
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
#define and &&
#define or ||
#define not !
// int createSemaphore(key_t accessKey,int initialValue){
//     int semaphoreId;
//     do{
//         semaphoreId = semget(accessKey,1,IPC_CREAT | 0664);
//         if(semaphoreId == -1) printf("Error creating semaphore...\n");
//     }while(semaphoreId == -1);
//     semctl(semaphoreId, 0, SETVAL,initialValue);
//     return semaphoreId;
// }
// void downSemaphore(int semaphoreId){
//    struct sembuf op_p[]={0,-1,0};
//    semop(semaphoreId,op_p,1);
// }
// void upSemaphore(int semaphoreId){
//    struct sembuf op_v[]={0,+1,0};
//    semop(semaphoreId,op_v,1);
// }
typedef struct Client Client;
typedef struct ClientList ClientList;
struct Client{
    pid_t id;
    Client *next, *prev;
};
#define this ClientList* self
struct ClientList{
    Client *head,*tail;
    size_t size;
};
void ctr(this){
    self->head = self->tail = malloc(sizeof(Client));
    self->size = 0;
}
void push(this,int processId){
    Client *new = (Client*) malloc(sizeof(Client));
    new->id = processId;
    if(self->head == NULL or self->size == 0){
        self->head = self->tail = new;
        self->tail->prev = self->head;
        self->head->next = self->tail;
    }else{
        self->tail->next = new;
        new->prev = self->tail;
        self->tail = new;
    }
    self->size++;
}
void popLast(this){
    if(self->size-1 > 0){
        self->size--;
        Client *tmp = self->tail;
        self->tail = self->tail->prev;
        free(tmp);
    }
}
void popFront(this){
    if(self->size > 0){
        self->size--;
        self->head = self->head->next;
    }
}
int getValue(Client client){
    return client.id;
}
void PrintList(ClientList list){
    while(list.size > 0){
        printf("crash? %ld \n",list.size);
        int id = getValue(*list.head);
        printf("id: %d\n",id);
        popFront(&list);
    }
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
void clearSharedMemory(int sharedMemoryId){
    while(shmctl(sharedMemoryId,0,NULL) != 0);
}
