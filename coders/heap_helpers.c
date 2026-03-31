/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heap_helpers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/31 21:01:46 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/03/31 21:01:59 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

int	get_left_child(int i)
{
	return (2 * i + 1);
}

int	get_right_child(int i)
{
	return (2 * i + 2);
}

int	get_parent(int i)
{
	return ((i - 1) / 2);
}