#include "coders.h"

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}