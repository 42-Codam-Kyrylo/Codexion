#include "coders.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	init_start_time(t_data *data)
{
	long long	time;

	time = get_current_time();
	if (!time)
		return (1);
	data->start_time = time;
	return (0);
}

int	init_coders(t_data *data)
{
	int	i;

	data->coders = malloc(sizeof(t_coder) * data->number_of_coders);
	if (!data->coders)
		return (1);
	i = 0;
	while (i < data->number_of_coders)
	{
		t_coder coder = {
			.id = i + 1,
			.status = CODER_INITIALIZING,
			.data = data,
			.compiles_done = 0,
		};
		data->coders[i] = coder;
		i++;
	}
	return (0);
}

int	start_coders(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->number_of_coders)
	{
		status = pthread_create(&data->coders[i].thread, NULL, coder_routine,
				(void *)&data->coders[i]);
		if (status != 0)
		{
			fprintf(stderr, "Error create: %s\n", strerror(status));
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_coders(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->number_of_coders)
	{
		status = pthread_join(data->coders[i].thread, NULL);
		if (status != 0)
		{
			fprintf(stderr, "Error join: %s\n", strerror(status));
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}