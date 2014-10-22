#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#define MAX_SOCKET 50
int sock_queue[MAX_SOCKET] = {0};
int sock_queue_head = 0;
int sock_queue_tail = 0;
sem_t queue_notempty;
sem_t queue_notfull;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
void push(int sockfd)
{
        sem_wait(&queue_notfull);
        pthread_mutex_lock(&queue_mutex);
        sock_queue[sock_queue_tail++] = sockfd;
        if (sock_queue_tail == MAX_SOCKET)
                sock_queue_tail = 0;
        pthread_mutex_unlock(&queue_mutex);
        sem_post(&queue_notempty);
}

int pop()       //block threadpool
{
        int ret = 0;
        sem_wait(&queue_notempty);
        pthread_mutex_lock(&queue_mutex);
        ret = sock_queue[sock_queue_head++];
        if (sock_queue_head == MAX_SOCKET)
                sock_queue_head = 0;
        pthread_mutex_unlock(&queue_mutex);
        sem_post(&queue_notfull);
        return ret;
}

void print()
{
	int i;
	printf("stack: ");
	if (sock_queue_head <= sock_queue_tail)
	{
		for (i = sock_queue_head; i < sock_queue_tail; i++)
			printf("%d ", sock_queue[i]);
	}
	else
	{
		for (i = sock_queue_head; i < MAX_SOCKET; i++)
			printf("%d ", sock_queue[i]);
		for (i = 0; i < sock_queue_tail; i++)
			printf("%d ", sock_queue[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	int i;
	sem_init(&queue_notempty, 0, 0);
	sem_init(&queue_notfull, 0, MAX_SOCKET);
	push(3);
	push(4);
	pop();
	print();
	for (i = 0; i < MAX_SOCKET-2; i++)
	{
		push(i);
		print();
	}
	for (i = 0; i < MAX_SOCKET-1; i++)
	{
		pop();
		print();
	}
}
