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
 * @brief Checks if a node should bubble up in the min-heap.
 *
 * A node bubbles up if it has a lower priority than its parent.
 *
 * @param heap The heap structure.
 * @param i Index of the current node.
 * @return 1 if the node should bubble up, 0 otherwise.
 */
int	should_bubble_up(t_heap *heap, int i)
{
	if (i == 0)
		return (0);
	return (heap->array[get_parent(i)].priority > heap->array[i].priority);
}

/**
 * @brief Removes a node from the heap by coder ID.
 *
 * Finds the node with the given coder_id and removes it from the heap,
 * restoring heap order by moving the last element to the removed node's
 * position and re-heapifying as needed.
 *
 * @param heap The heap to remove from.
 * @param coder_id The ID of the coder to remove.
 * @return 1 if node was found and removed, 0 otherwise.
 */
int	pop_node_by_id(t_heap *heap, int coder_id)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->array[i].coder_id == coder_id)
		{
			heap->array[i] = heap->array[heap->size - 1];
			heap->size--;
			if (i < heap->size && should_bubble_up(heap, i))
				bubble_up_from(heap, i);
			else if (i < heap->size)
				heapify(heap, i);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Bubbles a node up from the given index.
 *
 * @param heap The heap structure.
 * @param i Index from which to start bubbling up.
 */
void	bubble_up_from(t_heap *heap, int i)
{
	while (should_bubble_up(heap, i))
	{
		swap_heap(&heap->array[i], &heap->array[get_parent(i)]);
		i = get_parent(i);
	}
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