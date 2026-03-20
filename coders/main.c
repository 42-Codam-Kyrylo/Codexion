/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/20 14:14:25 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/03/20 18:19:51 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <stdio.h>
#include <stdlib.h>

void	print_data(t_data *data);

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (parse(data, argc, argv) != 0)
	{
		free(data);
		return (1);
	}
	// work
	print_data(data);
	free(data);
	return (0);
}

void	print_data(t_data *data)
{
	const char *scheduler;

	if (!data)
		return ;
	if (data->scheduler == SCHED_FIFO)
		scheduler = "FIFO";
	else if (data->scheduler == SCHED_EDF)
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