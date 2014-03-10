#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main (){
  int segment_id;
  char* shared_memory;
  struct shmid_ds shmbuffer;
  int segment_size;
  const int shared_segment_size = 0x6400;
  /* Allocate a shared memory segment. */
  segment_id = shmget (IPC_PRIVATE, shared_segment_size, 
			IPC_CREAT |IPC_EXCL |S_IRUSR |S_IWUSR);
  /* Attach the shared memory segment. */
  shared_memory = (char*) shmat (segment_id, 0, 0); 
  printf ("shared memory with id %d attached at address %p\n", segment_id, shared_memory);
  /* Determine the segments size. */
  shmctl (segment_id, IPC_STAT, &shmbuffer); 
  segment_size = shmbuffer.shm_segsz;
  printf ("segment size: %d\n", segment_size);
  /* Write a string to the shared memory segment. */
  sprintf (shared_memory, "Hello, world."); 
  shmdt (shared_memory); /* Detach the shared memory segment. */
  /* Reattach the shared memory segment, at a different address. */
  shared_memory = (char*) shmat (segment_id, (void*) 0x5000000, 0); 
  printf ("shared memory reattached at address %p\n", shared_memory);
  printf ("%s\n", shared_memory); 
  printf ("Sleep for 10s\n");
  sleep(10);
  shmdt (shared_memory); /* Detach the shared memory segment. */
  /* Deallocate the shared memory segment. */
  shmctl (segment_id, IPC_RMID, 0); 
  printf("Completely remove shared memory\n");
  return 0;
}