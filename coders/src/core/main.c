/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+#+#+#+#+
	+#+           */
/*   Created: 2026/03/20 14:14:25 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/04/07 22:18:11 by kvolynsk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <stdio.h>
#include <stdlib.h>

void		print_data(t_data *data);

static int	cleanup_data(t_data *data, int destroy_core_mutexes,
		int destroy_dongles, int destroy_dongle_mutexes)
{
	if (destroy_dongles)
		cleanup_dongles_range(data, data->number_of_coders,
			destroy_dongle_mutexes);
	if (destroy_core_mutexes)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		pthread_mutex_destroy(&data->print_mutex);
	}
	free(data->coders);
	free(data);
	return (1);
}

static int	init_resources(t_data *data, int *core_mutexes, int *dongles,
		int *dongle_mutexes)
{
	*core_mutexes = 0;
	*dongles = 0;
	*dongle_mutexes = 0;
	if (init_data_mutexes(data) != 0)
		return (1);
	*core_mutexes = 1;
	if (init_dongles(data) != 0)
		return (1);
	*dongles = 1;
	if (init_dongle_mutexes(data) != 0)
		return (1);
	*dongle_mutexes = 1;
	return (0);
}

static int	launch_coders(t_data *data)
{
	if (init_start_time(data) != 0)
		printf("Error: init_start_time failed\n");
	else if (init_coders(data) != 0)
		printf("Error: init_coders failed\n");
	else if (start_coders(data) != 0)
		printf("Error: start_coders failed\n");
	else if (join_coders(data) != 0)
		printf("Error: join_coders failed\n");
	else
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		core_mutexes;
	int		dongles;
	int		dongle_mutexes;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	*data = (t_data){0};
	if (parse(data, argc, argv) != 0)
	{
		free(data);
		return (1);
	}
	if (init_resources(data, &core_mutexes, &dongles, &dongle_mutexes) != 0)
	{
		return (cleanup_data(data, core_mutexes, dongles, dongle_mutexes));
	}
	print_data(data);
	if (launch_coders(data) != 0)
		return (cleanup_data(data, core_mutexes, dongles, dongle_mutexes));
	cleanup_data(data, core_mutexes, dongles, dongle_mutexes);
	return (0);
}

void	print_data(t_data *data)
{
	const char *scheduler;

	if (!data)
		return ;
	if (data->scheduler == CODERS_SCHED_FIFO)
		scheduler = "FIFO";
	else if (data->scheduler == CODERS_SCHED_EDF)
		scheduler = "EDF";
	else
		scheduler = "UNKNOWN";
	printf("number_of_coders: %d\n", data->number_of_coders);
	printf("time_to_burnout: %lld\n", data->time_to_burnout);
	printf("time_to_compile: %lld\n", data->time_to_compile);
	printf("time_to_debug: %lld\n", data->time_to_debug);
	printf("time_to_refactor: %lld\n", data->time_to_refactor);
	printf("number_of_compiles_required: %d\n",
		data->number_of_compiles_required);
	printf("dongle_cooldown: %lld\n", data->dongle_cooldown);
	printf("scheduler: %s\n", scheduler);
}