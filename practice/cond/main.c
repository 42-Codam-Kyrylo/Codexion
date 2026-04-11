#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				is_ready;
}					t_shared_data;

void *consumer(void *arg) {
	t_shared_data *data = (t_shared_data *)arg;

	pthread_mutex_lock(&data->mutex);

	while(data->is_ready == 0) {
		printf("[Consumer] No data, go sleep...\n");

		pthread_cond_wait(&data->cond, &data->mutex);

		printf("[Consumer] waked up, check condition again\n");
	}

	printf("[Consumer] Yeah! Got data!\n");
	pthread_mutex_unlock(&data->mutex);
	return NULL;
}

void *producer(void *arg) {
	t_shared_data *data = (t_shared_data *)arg;

	sleep(2);

	pthread_mutex_lock(&data->mutex);
	printf("[Producer] Preparing data...\n");

	data->is_ready = 1;

	printf("[Producer] sending signal to consumer\n");
	pthread_cond_broadcast(&data->cond);
	pthread_mutex_unlock(&data->mutex);
	return NULL;	
}

int	main(void)
{
	t_shared_data	data;
	pthread_t thread_c, thread_p;

	data.is_ready = 0;
	pthread_mutex_init(&data.mutex, NULL);
	pthread_cond_init(&data.cond, NULL);

	pthread_create(&thread_c, NULL, consumer, &data);
	pthread_create(&thread_p, NULL, producer, &data);

	pthread_join(thread_c, NULL);
	pthread_join(thread_p, NULL);

	pthread_mutex_destroy(&data.mutex);
	pthread_cond_destroy(&data.cond);

	return 0;
}
