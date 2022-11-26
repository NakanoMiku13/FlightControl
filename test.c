#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define PERMISOS 0644

int Crea_semaforo(key_t llave,int valor_inicial)
{
   int semid=semget(llave,1,IPC_CREAT|PERMISOS);
   if(semid==-1)
   {
      return -1;
   }
   semctl(semid,0,SETVAL,valor_inicial);
   return semid;
}

void down(int semid)
{
   struct sembuf op_p[]={0,-1,0};
   semop(semid,op_p,1);
}

void up(int semid)
{
   struct sembuf op_v[]={0,+1,0};
   semop(semid,op_v,1);
}

int main()
{
   int i=5,semaforo;
   pid_t pid;
   key_t llave;
   llave=ftok("Prueba",'k'); 
   semaforo=Crea_semaforo(llave,1);
   pid=fork();
   if(pid==0)
   {
      while(i)
      {
         printf("Hijo con pid %d...Fuera de la region critica\n",getpid());
         down(semaforo);
         printf("Hijo en la region critica %d...\n",i--);
         sleep(i);
         up(semaforo);
      }
   }
   else
   {
      while(i)
      {
         printf("Padre con pid %d...Fuera de la region critica \n",getpid());
         down(semaforo);
         printf("Padre en la region critica %d...\n",i--);
         sleep(i);
         up(semaforo);
      }
   }
}