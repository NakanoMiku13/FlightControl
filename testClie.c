#include "Project.h"
int main(){
    clientConnect(getpid());
    int n = 0;
    do{
        scanf("%d",&n);
        printf("Shared memory is %d\n",getpid());
    }while(n!=908);
    releaseConnection();
}