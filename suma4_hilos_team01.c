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
void *thread_sum3(void *arg);
void *thread_sum4(void *arg);

//Declarando semáforo
sem_t bin_one, bin_two, bin_three, bin_four;

//Variable de precompilación para nuestro número
#define limit_num 1000000000
#define fragments_num 4

//Variable bandera
int readyt1 = 0, readyt2 = 0, readyt3 = 0, readyt4 = 0;
long double acum = 0;

int main(){
  int res;
  pthread_t a_thread, b_thread, c_thread, d_thread;
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

  //Creando semáforo 3
  res = sem_init(&bin_three, 0,0);
  if(res != 0){
    perror("Semaphore 3 inizialization failed!");
    exit(EXIT_FAILURE);
  }

  //Creando semáforo 4
  res = sem_init(&bin_four, 0, 0);
  if(res != 0){
    perror("Semaphore 4 inizialization failed!");
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

  //Creando hilo 3
  res = pthread_create(&c_thread, NULL, thread_sum3, NULL);
  if(res != 0){
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }
  
  //Creando hilo 4
  res = pthread_create(&d_thread, NULL, thread_sum4, NULL);
  if(res != 0){
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }

  printf("Running four threads\n");  

  time_t begin = time(NULL);
  sem_post(&bin_one);
  sem_post(&bin_two);
  sem_post(&bin_three);
  sem_post(&bin_four);

  while(readyt1 == 0 || readyt2 == 0 || readyt3 == 0 || readyt4 == 0){
    // printf("Calculating...\n");
  }

  time_t end = time(NULL);
  printf("El resultado es: %.0Lf\n",acum);
  printf("Tiempo de ejecución: %.0ld segundos\n",end-begin);

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
  res = pthread_join(c_thread, &thread_result);
  if(res != 0){
    perror("Thread 3 join failed!\n");
    exit(EXIT_FAILURE);
  }
  res = pthread_join(d_thread, &thread_result);
  if(res != 0){
    perror("Thread 4 join failed!\n");
    exit(EXIT_FAILURE);
  }

  printf("Threads joined\n");
  sem_destroy(&bin_one);
  sem_destroy(&bin_two);
  sem_destroy(&bin_three);
  sem_destroy(&bin_four);
  exit(EXIT_FAILURE);
  return 0;
}

void *thread_sum1(void *arg){
  sem_wait(&bin_one);
  int contador;
	long double total = 0;
  for (contador = 1; contador < limit_num/fragments_num; contador++) {
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
  for (contador = limit_num / fragments_num; contador < (limit_num / fragments_num) * 2; contador++) {
    total +=contador;
  }
  acum += total;
  // printf("Total 2: %.0Lf\n total so far: %.0Lf\n", total, acum);
  readyt2 = 1;
  pthread_exit(NULL);
}

void *thread_sum3(void *arg){
  sem_wait(&bin_three);
  int contador;
	long double total = 0;
  for (contador = (limit_num / fragments_num) * 2; contador < (limit_num / fragments_num) * 3; contador++) {
    total +=contador;
  }
  acum += total;
  // printf("Total 2: %.0Lf\n total so far: %.0Lf\n", total, acum);
  readyt3 = 1;
  pthread_exit(NULL);
}

void *thread_sum4(void *arg){
  sem_wait(&bin_four);
  int contador;
	long double total = 0;
  for (contador = (limit_num / fragments_num) * 3; contador <= (limit_num / fragments_num) * 4; contador++) {
    total +=contador;
  }
  acum += total;
  // printf("Total 2: %.0Lf\n total so far: %.0Lf\n", total, acum);
  readyt4 = 1;
  pthread_exit(NULL);
}