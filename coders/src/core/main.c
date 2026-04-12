/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/20 14:14:25 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/04/12 21:13:30 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <stdio.h>
#include <stdlib.h>

void		print_data(t_data *data);
static int	cleanup_data(t_data *data, int cleanup_state);
static int	init_resources(t_data *data, int *cleanup_state);
int			launch_simulation(t_data *data);

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		cleanup_state;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	*data = (t_data){0};
	if (parse(data, argc, argv) != 0)
		return (free(data), 1);
	if (init_resources(data, &cleanup_state) != 0)
		return (cleanup_data(data, cleanup_state));
	if (launch_simulation(data) != 0)
		return (cleanup_data(data, cleanup_state));
	cleanup_data(data, cleanup_state);
	return (0);
}

static int	init_resources(t_data *data, int *cleanup_state)
{
	*cleanup_state = 0;
	if (init_data_mutexes(data) != 0)
		return (1);
	*cleanup_state |= CLEANUP_CORE_MUTEXES;
	if (init_dongles(data) != 0)
		return (1);
	*cleanup_state |= CLEANUP_DONGLES;
	if (init_dongle_mutexes(data) != 0)
		return (1);
	*cleanup_state |= CLEANUP_DONGLE_MUTEXES;
	if (init_dongle_conds(data) != 0)
		return (1);
	*cleanup_state |= CLEANUP_DONGLE_CONDS;
	if (init_start_time(data) != 0)
		return (1);
	if (init_coders(data) != 0)
		return (1);
	*cleanup_state |= CLEANUP_CODERS;
	if (init_coder_mutexes(data) != 0)
		return (1);
	*cleanup_state |= CLEANUP_CODER_MUTEXES;
	return (0);
}

static int	cleanup_data(t_data *data, int cleanup_state)
{
	if (cleanup_state & CLEANUP_DONGLES)
		cleanup_dongles_range(data, data->number_of_coders,
			cleanup_state & CLEANUP_DONGLE_MUTEXES,
			cleanup_state & CLEANUP_DONGLE_CONDS);
	if (cleanup_state & CLEANUP_CODERS)
		cleanup_coders_range(data, data->number_of_coders,
			cleanup_state & CLEANUP_CODER_MUTEXES);
	if (cleanup_state & CLEANUP_CORE_MUTEXES)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		pthread_mutex_destroy(&data->print_mutex);
	}
	free(data);
	return (1);
}

// void	print_data(t_data *data)
// {
// 	const char	*scheduler;

// 	if (!data)
// 		return ;
// 	if (data->scheduler == CODERS_SCHED_FIFO)
// 		scheduler = "FIFO";
// 	else if (data->scheduler == CODERS_SCHED_EDF)
// 		scheduler = "EDF";
// 	else
// 		scheduler = "UNKNOWN";
// 	printf("number_of_coders: %d\n", data->number_of_coders);
// 	printf("time_to_burnout: %lld\n", data->time_to_burnout);
// 	printf("time_to_compile: %lld\n", data->time_to_compile);
// 	printf("time_to_debug: %lld\n", data->time_to_debug);
// 	printf("time_to_refactor: %lld\n", data->time_to_refactor);
// 	printf("number_of_compiles_required: %d\n",
// 		data->number_of_compiles_required);
// 	printf("dongle_cooldown: %lld\n", data->dongle_cooldown);
// 	printf("scheduler: %s\n", scheduler);
// }
