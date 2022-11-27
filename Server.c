#include "Project.h"
int main(){
    Flight vuelo1 = defaultFlight();
    Flight* test = createSharedMemoryFlight();
    *test = vuelo1;
    key_t accessKey = ftok("Server",1234);
    int sharedMemoryId = createSharedMemoryId(accessKey), *connection = createSharedMemory(sharedMemoryId);
    *connection = 0;
    int count = 0, lastUser = -1;
    do{
        if(*connection == 0) printf("Waiting for a client...\n");
        else{
            int pid = fork();
            if(pid==-1) printf("Error unknown...\n");
            else if(pid == 0){
                printf("Client successfully connected: id: %d\n",*connection);
                printf("Flight id: %d\n",test->id);
                printf("Destination: %s\n",test->destination);
                printf("tt: %ld\n",sizeof(test->destination));
                *connection = 0;
                exit(1);
            }else{
                if(lastUser != *connection){
                    printf("New user connection detected...\n");
                }
            }
        }
        sleep(1);
    }while(connection >= 0);
    return 0;
}