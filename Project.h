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
#include<string.h>
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
#define and &&
#define or ||
#define not !
#define this TicketList* self
#define READNWRITE 00004|00002
#define clientServerConnectionKey (key_t)ftok("Server",79123)
#define flightSharedKey (key_t)ftok("Project.h",90878)
typedef struct Flight Flight;
typedef struct Ticket Ticket;
struct Ticket{
    int flightId,seatNumber,isAvailable;
    float price;
};
struct Flight{
    int id, isFull, ticketsCount;
    char destination[250];
    Ticket tickets[125];
};
static struct Flight* createSharedMemoryFlight(void){
    void *sharedMemory = (void *)0;
    int sharedMemoryId = shmget(flightSharedKey,sizeof(struct Flight),IPC_CREAT | 0644);
    if (sharedMemoryId == -1) {
        printf("Error unknown...\n");
    }
    sharedMemory = (struct Flight*) shmat(sharedMemoryId,(struct Flight*)0,0);
    if(sharedMemory == (void*)-1){
        printf("Error unknown...\n");
    }
    return sharedMemory;
}
static struct Flight* getSharedMemoryFlight(void){
    void *sharedMemory = (void *)0;
    int sharedMemoryId = shmget(flightSharedKey,sizeof(struct Flight),IPC_CREAT | 0644);
    if (sharedMemoryId == -1) {
        printf("Error unknown...\n");
    }
    sharedMemory = (struct Flight*) shmat(sharedMemoryId,(struct Flight*)0,0);
    if(sharedMemory == (void*)-1){
        printf("Error unknown...\n");
    }
    return sharedMemory;
}
Flight createFlight(const int id,char destination[],const int ticketsCount,const float price){
    Flight flight;
    flight.id = id;
    strcpy(flight.destination, destination);
    flight.ticketsCount = ticketsCount;
    flight.isFull = FALSE;
    int i = 0;
    for(i = 0; i < flight.ticketsCount; i++){
        Ticket ticket;
        ticket.flightId = id;
        ticket.seatNumber = i+1;
        ticket.isAvailable = TRUE;
        ticket.price = price;
        flight.tickets[i] = ticket;
    }
    return flight;
}
Flight defaultFlight(){
    Flight flight;
    flight.id = 1;
    strcpy(flight.destination,"Cancun");
    flight.ticketsCount = 10;
    flight.isFull = FALSE;
    int i = 0;
    for(i = 0; i < flight.ticketsCount; i++){
        Ticket ticket;
        ticket.flightId = 1;
        ticket.seatNumber = i+1;
        ticket.isAvailable = TRUE;
        ticket.price = 150;
        flight.tickets[i] = ticket;
    }
    return flight;
}
int createSharedMemoryId(int accessKey){
    int sharedMemoryId;
    do{
        sharedMemoryId = shmget(accessKey,sizeof(int),IPC_CREAT|0666);
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
void clearSharedMemory(int sharedMemoryId){
    while(shmctl(sharedMemoryId,0,NULL) != 0);
}

int createSharedMemoryIdFlightInfo(Flight flight){
    int sharedMemoryId;
    do{
        sharedMemoryId = shmget(flightSharedKey,sizeof(Flight),READNWRITE);
        if(sharedMemoryId < 0) printf("Error sending the Flight Information\nTrying again...\n");
    }while(sharedMemoryId < 0);
    return sharedMemoryId;
}
Flight* setSharedMemory(const int flightSharedMemoryId){
    Flight* flight = (Flight*)malloc(sizeof(Flight));
    do{
        flight = (Flight*)shmat(flightSharedMemoryId,0,READNWRITE);
        if(flight == NULL or flight == (Flight*)-1){ printf("Error unknown...\nTrying again...\n"); sleep(5);}
    }while(flight == NULL or flight == (Flight*)-1);
    return flight;
}
void clientConnect(const int pid){
    int *sharedMemory = createSharedMemory(createSharedMemoryId(clientServerConnectionKey));
    *sharedMemory = pid;
}
void releaseConnection(){
    int *sharedMemory = createSharedMemory(createSharedMemoryId(clientServerConnectionKey));
    *sharedMemory = 0;
}