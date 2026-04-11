/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heap_helpers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+#+#+#+#+
	+#+           */
/*   Created: 2026/03/31 21:01:46 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/03/31 21:01:59 by kvolynsk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <stdio.h>

/**
 * @brief Returns the index of the left child in the heap array.
 *
 * @param i Current node index.
 * @return Left child index.
 */
int	get_left_child(int i)
{
	return (2 * i + 1);
}

/**
 * @brief Returns the index of the right child in the heap array.
 *
 * @param i Current node index.
 * @return Right child index.
 */
int	get_right_child(int i)
{
	return (2 * i + 2);
}

/**
 * @brief Returns the index of the parent node in the heap array.
 *
 * @param i Current node index.
 * @return Parent index.
 */
int	get_parent(int i)
{
	return ((i - 1) / 2);
}

/**
 * @brief Returns the priority value for the current scheduler.
 *
 * Uses request time for FIFO and deadline time for EDF.
 *
 * @param coder Current coder.
 * @return Priority value used by the heap.
 */
long long	get_node_priority(t_coder *coder)
{
	if (coder->data->scheduler == CODERS_SCHED_FIFO)
	{
		return (get_current_time());
	}
	if (coder->data->scheduler == CODERS_SCHED_EDF)
	{
		return (coder->last_compiling_at + coder->data->time_to_burnout);
	}

	printf("uknown scheduler!");
	return (0);
}