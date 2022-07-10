#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int main(){
	long double total,contador;
	total=0;
	time_t begin = time(NULL);
    for (contador = 1; contador <= 1000000000; contador++) {  
     total += contador;
    }
  time_t end = time(NULL);
	
	printf("suma %.0Lf \n",total);
  printf("Tiempo de ejcución es de: %ld segundos \n",(end-begin));
}

