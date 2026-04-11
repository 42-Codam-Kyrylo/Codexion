/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder_helpers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/11 15:11:00 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/04/11 15:11:00 by kvolynsk      ########   odam.nl         */
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
/**
 * @brief Computes a deterministic dongle lock order for one coder.
 *
 * Gets the coder's two dongle indices and stores them in ascending order
 * so all threads lock dongles consistently and avoid deadlocks.
 *
 * @param coder Current coder.
 * @param first Output: lower dongle index to lock first.
 * @param second Output: higher dongle index to lock second.
 */
void	get_dongle_lock_order(t_coder *coder, int *first, int *second)
{
	int	leftDongleIdx;
	int	rightDongleIdx;

	leftDongleIdx = coder->id - 1;
	rightDongleIdx = (leftDongleIdx - 1 + coder->data->number_of_coders)
		% coder->data->number_of_coders;
	if (leftDongleIdx < rightDongleIdx)
	{
		*first = leftDongleIdx;
		*second = rightDongleIdx;
	}
	else
	{
		*first = rightDongleIdx;
		*second = leftDongleIdx;
	}
}
