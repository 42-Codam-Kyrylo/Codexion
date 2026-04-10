/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heap.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+#+#+#+#+  
	+#+           */
/*   Created: 2026/03/31 19:20:07 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/03/31 22:10:04 by kvolynsk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <stdio.h>
#include <stdlib.h>

t_heap	*create_heap(int capacity)
{
	t_heap	*heap;

	heap = (t_heap *)malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->size = 0;
	heap->capacity = capacity;
	heap->array = (t_node *)malloc(capacity * sizeof(t_node));
	if (!heap->array)
	{
		free(heap);
		return (NULL);
	}
	return (heap);
}
void	swap_heap(t_node *a, t_node *b)
{
	t_node	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
void	insert_heap(t_heap *heap, t_node node)
{
	int	i;

	if (heap->size == heap->capacity)
	{
		printf("ERROR: heap overflow!\n");
		return ;
	}
	i = heap->size;
	heap->size++;
	heap->array[i] = node;
	while (i != 0
		&& heap->array[get_parent(i)].priority > heap->array[i].priority)
	{
		swap_heap(&heap->array[i], &heap->array[get_parent(i)]);
		i = get_parent(i);
	}
}

void	heapify(t_heap *heap, int i)
{
	int	smallest;
	int	left;
	int	right;

	smallest = i;
	left = get_left_child(i);
	right = get_right_child(i);
	if (left < heap->size
		&& heap->array[left].priority < heap->array[smallest].priority)
		smallest = left;
	if (right < heap->size
		&& heap->array[right].priority < heap->array[smallest].priority)
		smallest = right;
	if (smallest != i)
	{
		swap_heap(&heap->array[i], &heap->array[smallest]);
		heapify(heap, smallest);
	}
}

t_node	pop_heap(t_heap *heap)
{
	t_node head;

	if (heap->size <= 0)
		return ((t_node){0, -1});
	head = heap->array[0];
	heap->array[0] = heap->array[heap->size - 1];
	heap->size--;
	heapify(heap, 0);
	return (head);
}