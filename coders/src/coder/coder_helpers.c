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

void	print_status(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->data->print_mutex);
	if (!get_is_simulation_end(coder->data))
		printf("%lld %d %s\n", get_timestamp(coder->data->start_time),
			coder->id, msg);
	pthread_mutex_unlock(&coder->data->print_mutex);
}
