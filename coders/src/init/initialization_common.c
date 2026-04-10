#include "coders.h"

int	init_start_time(t_data *data)
{
	long long	time;

	time = get_current_time();
	if (!time)
		return (1);
	data->start_time = time;
	return (0);
}

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}
