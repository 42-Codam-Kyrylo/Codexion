/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/11 17:30:00 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/04/15 20:08:14 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

/**
 * @brief Builds the absolute wake-up time for a dongle cooldown wait.
 *
 * @param dongle Dongle being checked.
 * @param data Shared simulation data.
 * @param ts Output timespec for timed waiting.
 */
void	prepare_dongle_wait_time(t_dongle *dongle, t_data *data,
		struct timespec *ts)
{
	long long	wait_until_ms;

	wait_until_ms = dongle->last_released_at + data->dongle_cooldown;
	ts->tv_sec = wait_until_ms / 1000;
	ts->tv_nsec = (wait_until_ms % 1000) * 1000000;
}

/**
 * @brief Checks whether the coder may acquire this dongle now.
 *
 * Requires a free dongle, cooldown elapsed, and this coder at queue head.
 *
 * @param dongle Target dongle.
 * @param coder Current coder.
 * @return 1 if the coder can take the dongle, otherwise 0.
 */
int	can_take_dongle(t_dongle *dongle, t_coder *coder)
{
	long	elapsed;

	elapsed = get_current_time() - dongle->last_released_at;
	return (dongle->status == DONGLE_FREE
		&& elapsed >= coder->data->dongle_cooldown
		&& dongle->queue->array[0].coder_id == coder->id);
}
