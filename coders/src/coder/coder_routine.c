#include "coders.h"
#include <stdio.h>
#include <unistd.h>

int	get_is_simulation_end(t_data *data)
{
	int	is_end;

	pthread_mutex_lock(&data->stop_mutex);
	is_end = data->is_simulation_end;
	pthread_mutex_unlock(&data->stop_mutex);
	return (is_end);
}

void	print_status(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->data->print_mutex);
	if (!get_is_simulation_end(coder->data))
		printf("%lld %d %s\n", get_timestamp(coder->data->start_time),
			coder->id, msg);
	pthread_mutex_unlock(&coder->data->print_mutex);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!get_is_simulation_end(coder->data))
	{
		print_status(coder, "is compiling");
		ft_sleep(coder->data->time_to_compile);
		if (get_is_simulation_end(coder->data))
			return (NULL);
		print_status(coder, "is debugging");
		ft_sleep(coder->data->time_to_debug);
		if (get_is_simulation_end(coder->data))
			return (NULL);
		print_status(coder, "is refactoring");
		ft_sleep(coder->data->time_to_refactor);
		coder->compiles_done++;
	}
	return (NULL);
}

void	ft_sleep(long long time)
{
	usleep(time * 1000);
}

long long	get_timestamp(long long simulation_start_time)
{
	return (get_current_time() - simulation_start_time);
}