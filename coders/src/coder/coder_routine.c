/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/10 21:46:24 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/04/10 21:46:25 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <unistd.h>

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!get_is_simulation_end(coder->data))
	{
		update_compiling_at(coder);
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