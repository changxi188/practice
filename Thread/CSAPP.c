#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// global shared variable
volatile long cnt = 0;

void *thread(void *vargp){

	long i, niter = *((long *) vargp);
	
	for (i = 0; i < niter; ++i){

		cnt++;
	}
	return NULL;
}

int main(int argc, char **argv){

	long niters;
	pthread_t tid1, tid2;

	niters = atoi(argv[1]);
	pthread_create(&tid1, NULL, thread, &niters);
	pthread_create(&tid2, NULL, thread, &niters);

	// check result

	if (cnt != (2 * niters)){
		printf("error, %ld\n", cnt);
	} else
	{
		printf("ok, %ld\n", cnt);
	}
	
}
