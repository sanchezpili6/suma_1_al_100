#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

//Declaración de la función que usaran las hilos
void *thread_sum1(void *arg);
void *thread_sum2(void *arg);

//Declarando semáforo
sem_t bin_one, bin_two;

//Variable de precompilación para nuestro número
#define limit_num 1000000000

//Variable bandera
int readyt1 = 0, readyt2 = 0;
long double acum = 0;

int main(){
  int res;
  pthread_t a_thread, b_thread;
  void *thread_result;

  //Creando semáforo 1
  res = sem_init(&bin_one, 0,0);
  if(res != 0){
    perror("Semaphore 1 inizialization failed!");
    exit(EXIT_FAILURE);
  }

  //Creando semáforo 2
  res = sem_init(&bin_two, 0, 0);
  if(res != 0){
    perror("Semaphore 2 inizialization failed!");
    exit(EXIT_FAILURE);
  }

  //Creando hilo 1
  res = pthread_create(&a_thread, NULL, thread_sum1, NULL);
  if(res != 0){
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }
  
  //Creando hilo 2
  res = pthread_create(&b_thread, NULL, thread_sum2, NULL);
  if(res != 0){
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }
  
  printf("Running two threads\n");
  sem_post(&bin_one);
  sem_post(&bin_two);

  while(readyt1 == 0 || readyt2 == 0){
    // printf("Calculating...\n");
  }

  printf("El resultado es: %.0Lf\n",acum);

  //Esperar a que los hilos se unan
  res = pthread_join(a_thread, &thread_result);
  if(res != 0){
    perror("Thread 1 join failed!\n");
    exit(EXIT_FAILURE);
  }
  res = pthread_join(b_thread, &thread_result);
  if(res != 0){
    perror("Thread 2 join failed!\n");
    exit(EXIT_FAILURE);
  }
  printf("Threads joined\n");
  sem_destroy(&bin_one);
  sem_destroy(&bin_two);
  exit(EXIT_FAILURE);

  return 0;
}

void *thread_sum1(void *arg){
  sem_wait(&bin_one);
  int contador;
	long double total = 0;
  for (contador = 1; contador < limit_num/2; contador++) {
    total += contador;
  }
  acum += total;
  // printf("Total 1: %.0Lf\n total so far: %.0Lf\n", total, acum);
  readyt1 = 1;  
  pthread_exit(NULL);
}

void *thread_sum2(void *arg){
  sem_wait(&bin_two);
  int contador;
	long double total = 0;
  for (contador = limit_num / 2; contador <= limit_num; contador++) {
    total +=contador;
  }
  acum += total;
  // printf("Total 2: %.0Lf\n total so far: %.0Lf\n", total, acum);
  readyt2 = 1;
  pthread_exit(NULL);
}
