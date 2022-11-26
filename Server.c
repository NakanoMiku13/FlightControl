#include "Project.h"
int main(){
    key_t accessKey = ftok("Server",1234);
    int sharedMemoryId = createSharedMemoryId(accessKey), *sharedMemory = createSharedMemory(sharedMemoryId);
    while(*sharedMemory != 908){
        printf("The value: %d\n",*sharedMemory);
        sleep(1);
    }
    printf("Se hizo lectura\n");
    while(shmctl(sharedMemoryId,0,NULL) != 0);
    return 0;
}