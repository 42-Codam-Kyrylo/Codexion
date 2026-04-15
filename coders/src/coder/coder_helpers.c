/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder_helpers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/11 15:11:00 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/04/14 22:22:45 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <stdio.h>

int	get_is_simulation_end(t_data *data)
{
	int	is_end;

	pthread_mutex_lock(&data->stop_mutex);
	is_end = data->is_simulation_end;
	pthread_mutex_unlock(&data->stop_mutex);
	return (is_end);
}

void	update_compiling_at(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->last_compiling_at = get_current_time();
	pthread_mutex_unlock(&coder->mutex);
}

void	print_status(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->data->print_mutex);
	if (!get_is_simulation_end(coder->data))
		printf("%lld %d %s\n", get_timestamp(coder->data->start_time),
			coder->id, msg);
	pthread_mutex_unlock(&coder->data->print_mutex);
}

void	increment_compiles_done(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compiles_done++;
	pthread_mutex_unlock(&coder->mutex);
}

void	get_dongle_lock_order(t_coder *coder, int *first, int *second)
{
	int	i;
	int	n;
	int	left_dongle;
	int	right_dongle;

	i = coder->id - 1;
	n = coder->data->number_of_coders;
	left_dongle = i;
	right_dongle = (i - 1 + n) % n;
	if (coder->id == 1)
	{
		*first = right_dongle;
		*second = left_dongle;
	}
	else
	{
		*first = left_dongle;
		*second = right_dongle;
	}
}
