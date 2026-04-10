/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialization_dongles.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/10 21:46:29 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/04/10 21:50:59 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	cleanup_dongles_range(t_data *data, int count, int destroy_mutexes)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (destroy_mutexes)
			pthread_mutex_destroy(&data->dongles[i].mutex);
		free(data->dongles[i].queue->array);
		free(data->dongles[i].queue);
		i++;
	}
	free(data->dongles);
	data->dongles = NULL;
}

int	init_dongles(t_data *data)
{
	int	i;

	data->dongles = malloc(sizeof(t_dongle) * data->number_of_coders);
	if (!data->dongles)
		return (1);
	i = 0;
	while (i < data->number_of_coders)
	{
		t_dongle dongle = {
			.id = i + 1,
			.status = DONGLE_FREE,
			.last_released_at = 0,
			.queue = create_heap(2),
		};
		if (!dongle.queue)
		{
			cleanup_dongles_range(data, i, 0);
			return (1);
		}
		data->dongles[i] = dongle;
		i++;
	}
	return (0);
}

int	init_dongle_mutexes(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		status = pthread_mutex_init(&data->dongles[i].mutex, NULL);
		if (status != 0)
		{
			cleanup_dongles_range(data, i, 1);
			fprintf(stderr, "Error mutex init dongle_mutex: %s\n",
				strerror(status));
			return (1);
		}
		i++;
	}
	return (0);
}
// TODO init and destroy cond
