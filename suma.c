#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int main(){
	long double total,contador;
	total=0;
    for (contador = 1; contador <= 1000000000; contador++) {  
     total += contador;
    }
	
	printf("suma %.0Lf \n",total);
}

