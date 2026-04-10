#include <pthread.h>
#include <stdio.h>

void	*foo(void *arg)
{
	printf("Created a new thread\n");
	return (NULL);
}

int	main(void)
{
	pthread_t thread1;

	pthread_create(&thread1, NULL, foo, NULL);
	pthread_join(thread1, NULL);
	return (0);
}