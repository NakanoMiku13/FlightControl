#include "Project.h"
int main(){
    clientConnect(getpid());
    Flight* flight = getSharedMemoryFlight();
    int n = 0;
    do{
        scanf("%d",&n);
        printf("Shared memory is %d\n",getpid());
        for(int i = 0;i<10;i++){
            printf("%f ",flight->tickets[i].price);
        }
        printf("Destination: %s\n",flight->destination);
        printf("\n");
    }while(n!=908);
    releaseConnection();
}