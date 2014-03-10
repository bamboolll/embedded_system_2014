
#include <stdio.h>	 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>   
#include <sys/ipc.h>     
#include <sys/shm.h>	 
struct country {
    char name[30];
    char capital_city[30];
    char currency[30];
    int population;
};

int main()
{
    int shm_id;	
    char* shm_addr; 	  
    int* countries_num;     int* stop;    

    struct country* countries; 
    struct shmid_ds shm_desc;    
    int i;		  

    shm_id = shmget(100, 2048, IPC_CREAT | 0777);
    if (shm_id == -1) {
        perror("main: shmget error ");
        exit(1);
    }

    shm_addr = shmat(shm_id, NULL, 0);
    if (!shm_addr) { 
        perror("main: shmat error ");
        exit(1);
    }

    countries_num = (int*) shm_addr;
    *countries_num = 0;
    stop =(int*) ((void*)shm_addr+sizeof(int));
    *stop=0;

    countries = (struct country*) 
                       ((void*)shm_addr+sizeof(int)*2);

    strcpy(countries[0].name, "U.S.A");
    strcpy(countries[0].capital_city, "Washington");
    strcpy(countries[0].currency, "U.S. Dollar");
    countries[0].population = 250000000;
    (*countries_num)++;

    strcpy(countries[1]. name, "Israel");
    strcpy(countries[1].capital_city, "Jerusalem");
    strcpy(countries[1].currency, "New Israeli Shekel");
    countries[1].population = 6000000;
    (*countries_num)++;

    strcpy(countries[2]. name, "France");
    strcpy(countries[2].capital_city, "Paris");
    strcpy(countries[2].currency, "Frank");
    countries[2].population = 30000000;
    (*countries_num)++;

    printf("Waiting for other process reading data \n"); 
    fflush(stdout);
    while (!(*stop)) {               
         sleep(1);
    }


    if (shmdt(shm_addr) == -1) {
        perror("main: shmdt: ");
    }

    // if (shmctl(shm_id, IPC_RMID, &shm_desc) == -1) {
        // perror("main: shmctl error ");
    // }

    printf("main writer finished \n");

    return 0;
}

