#include "lib.h"
#include <time.h>
#include <pthread.h>
 
void* thread1(void* data)
{
	int cnt = 0;
	while(1){
		printf("thread1 set...\n");
		set(cnt++);
		usleep(1000000);
	}
	return NULL;
}
 
void* thread2(void* data)
{
	while(1){
		printf("thread2 get...\n");
		get();
		usleep(500000);
	}
}
 
void main()
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &thread1, NULL);
	pthread_create(&thread_id, NULL, &thread2, NULL);
	while(1){
		usleep(10000000);
	}
	return;
}

