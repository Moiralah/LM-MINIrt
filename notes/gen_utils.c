/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:39:53 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 21:54:03 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Merges two sorted arrays of intersections.
void	sort(t_its **ori, t_its **l, t_its **r, int size)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while ((i + q) < size)
	{
		if (q >= ceil(((double) size) / 2))
			ori[i + q] = l[i];
		else if (i >= floor(((double) size) / 2))
			ori[q + i] = r[q];
		else if ((l[i]->len < r[q]->len))
			ori[i + q] = l[i];
		else
			ori[q + i] = r[q];
		if (q >= ceil(((double) size) / 2))
			i++;
		else if (i >= floor(((double) size) / 2))
			q++;
		else if ((l[i]->len < r[q]->len))
			i++;
		else
			q++;
	}
}

// Recursively merges and sorts an array of intersections.
t_its	**merge(t_its **ori, int size)
{
	t_its	**left;
	t_its	**right;
	int		mid;

	mid = floor(((double) size) / 2);
	if (mid == 0)
		return (ori);
	left = calloc(mid, sizeof(t_its *));
	if (!left)
		return (NULL);
	while (--mid >= 0)
		left[mid] = ori[mid];
	mid = ceil(((double) size) / 2);
	right = calloc(mid, sizeof(t_its *));
	if (!right)
		return (NULL);
	mid = floor(((double) size) / 2);
	while (++mid <= size)
		right[size - mid] = ori[mid - 1];
	left = merge(left, floor(((double) size) / 2));
	right = merge(right, ceil(((double) size) / 2));
	sort(ori, left, right, size);
	return (free(left), free(right), ori);
}
