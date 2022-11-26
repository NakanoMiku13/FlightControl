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
    key_t accessKey = ftok("Server",1234);
    int sharedMemoryId = createSharedMemoryId(accessKey), *sharedMemory = createSharedMemory(sharedMemoryId);
    while(*sharedMemory != 908){
        printf("The value: %d\n",*sharedMemory);
        sleep(1);
    }
    printf("Se hizo lectura\n");
    clearSharedMemory(sharedMemoryId);
    return 0;
}