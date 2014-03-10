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
    int* countries_num; 
    int* stop;


    struct country* countries; 
    struct shmid_ds shm_desc;
    int i;		     
    shm_id = shmget(100, 2048, 0777);
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
    stop = (int*) ((void*)shm_addr+sizeof(int));

    countries = (struct country*) 
                 ((void*)shm_addr+sizeof(int)*2);

    printf("Total %d \n",(*countries_num));
    
    for (i=0; i < (*countries_num) ; i++) {
        printf("Countery %d:\n", i+1);
        printf("  name: %s:\n", countries[i].name);
        printf("  capital city: %s:\n",  
                               countries[i].capital_city);
        printf("  currency: %s:\n", countries[i].currency);
        printf("  population: %d:\n", 
                                countries[i].population);
    }
     printf("Now try to stop writer \n");

    *stop=1;

    return 0;
}

