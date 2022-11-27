#include "Project.h"
int main(){
    clientConnect(getpid());
    Flight* flight = getSharedMemoryFlight();
    char logIn;
    printf("Do you want to log in (Y for yes)(N for no)?\n");
    scanf("%c",&logIn);
    if(logIn == 'N' or logIn == 'n'){
        releaseConnection();
        return 0;
    }
    int n = 0;
    do{
        printf("Connected to the server with id: %d\n",getpid());
        Ticket tickets[12];
        printf("The destinations available are: %s\n",flight->destination);
        printf("These are the seats available:\n");
        int amountOfTickets = 0;
        if(flight->ticketsCount > 0){
            for(int i = 0;i<flight->ticketsCount;i++){
                if(flight->tickets[i].isAvailable) printf("Seat: %d\n",flight->tickets[i].seatNumber);
            }
            printf("Type the number of tickets to buy:\n");
            scanf("%d",&amountOfTickets);
            int seatNumber;
            for(int i = 0;i < amountOfTickets;i++){
                printf("Write the seat number...\n");
                scanf("%d",&seatNumber);
                if(flight->tickets[seatNumber-1].isAvailable == TRUE){
                    tickets[i] = flight->tickets[seatNumber-1];
                    flight->tickets[seatNumber-1].isAvailable = FALSE;
                }else{
                    printf("Seat not available...\nTry another...\n");
                    i--;
                }
            }
        }else{
            printf("There is no more tickets available...\n");
        }
        printf("Do you want to finish?(Y for yes)(N for no)\n");
        char checkOut;
        getchar();
        scanf("%c",&checkOut);
        if(checkOut == 'Y' or checkOut=='y'){
            system("clear");
            printf("These are your tickets for: %s\n",flight->destination);
            for(int i = 0;i< amountOfTickets;i++){
                printf("Seat Number: %d\n",tickets[i].seatNumber);
            }
            n = 908;
        }
        printf("\n");
    }while(n!=908);
    releaseConnection();
}