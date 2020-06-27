#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

// thread routine prototype
void *thread(void *vargp);

sem_t connected_lock; // binary semaphore
sem_t operators; // counting semaphore

// id variable for threads
int next_id = 1;

// this function simulates a phone call and how it
// is handled. A call(thread) first attempt
// to connect to a line, if the line is busy,
// then it prints 'calling line, busy signal'
// if it is not busy, then 'avalible line, 
// call ringing' is printed and connected is updated
// if any operator is free then, the call
// proceeds and 'speaking to operator' is 
// printed. the ticket order is simulated by 
// sleeping for a few seconds and then 'ticket bought' 
// is printed and operator semaphore is updated. then
// connected is update and 'has hung up' is printed
void* phonecall(void* vargp) {
  static int NUM_OPERATORS = 3;
  static int NUM_LINES = 5;
  static int connected = 0;    // Callers that are connected
  int count = 1;
  int id = next_id++;

  while(1){
    sem_wait(&connected_lock);
    if(connected == NUM_LINES){
      if(count == 1){
        printf("Thread %i is calling line, busy signal \n", id);
        count = 0;
      }
      sem_post(&connected_lock);
      continue;
    }
    else{
      printf("Thread %i has available line, call ringing \n", id);
      connected ++;
      sem_post(&connected_lock);
      break;
    }
  }
  
  sem_wait(&operators);
  printf("Thread %i is speaking to operator \n", id);
  sleep(3);
  printf("Thread %i has bought a ticket! \n", id);
  sem_post(&operators);

  sem_wait(&connected_lock);
  connected--;
  sem_post(&connected_lock);
  printf("Thread %i has hung up! \n", id);
}

// the main function takes in arguments to
// get the number of calls to be simulated
// if it is less than 1 or more than 240,
// it exits and prints error message.
// it initializes the semaphores, both
// the binary(connected_lock) and the
// counting semaphore(operators) respectively.
// threads are creared using pthread_create 
// inside a for loop. They are reaped at the end
// by pthread_join inside a for loop.
int main(int argc, char **argv) {
  int Num_threads = atoi(argv[1]);
  pthread_t tid[Num_threads];

  sem_init(&connected_lock,0,1);
  sem_init(&operators,0,3);

  if(Num_threads > 240 || Num_threads < 1){
      printf("Invalid number of threads \n");
      exit(1);
  }

  for(int i = 0; i < Num_threads; i++){
    if((pthread_create(&tid[i], NULL, phonecall, NULL) != 0)){
      perror("Error creating thread");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < Num_threads; i++){
    pthread_join(tid[i],NULL);
  }

  return 0;
}
