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
    int sharedMemoryId = createSharedMemoryId(accessKey), *connection = createSharedMemory(sharedMemoryId);
    int *users = (int*)malloc(sizeof(int)*10);
    *connection = 0;
    int count = 0, lastUser = -1;
    do{
        if(*connection == 0) printf("Waiting for a client...\n");
        else{
            int pid = fork();
            if(pid==-1) printf("Error unknown...\n");
            else if(pid == 0){
                *connection = 0;
                exit(1);
            }else{
                if(lastUser != *connection){
                    
                }
            }
        }
        sleep(1);
    }while(connection >= 0);
    return 0;
}