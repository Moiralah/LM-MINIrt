/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_basic_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:47 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:48 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Multiplies each element of a vector by a scalar value.
t_tuple	*mult(t_tuple *t, double value)
{
	t_tuple	*new_v;
	int		i;

	i = -1;
	new_v = tuple(0.0);
	if (!new_v)
		return (NULL);
	new_v->val = malloc(t->size * sizeof(double));
	if (!new_v->val)
		return (NULL);
	new_v->size = t->size;
	while (++i < t->size)
	{
		new_v->val[i] = t->val[i];
		if (t->val[i] != 0)
			new_v->val[i] = t->val[i] * value;
	}
	return (new_v);
}

// Subtracts one vector from another element-wise.
t_tuple	*sub(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*new_v;
	int		i;

	i = -1;
	if (tuple1->size != tuple2->size)
		return (NULL);
	new_v = tuple(0.0);
	if (!new_v)
		return (NULL);
	new_v->val = malloc(tuple1->size * sizeof(double));
	if (!new_v->val)
		return (NULL);
	new_v->size = tuple1->size;
	while (++i < tuple1->size)
		new_v->val[i] = tuple1->val[i] - tuple2->val[i];
	return (new_v);
}

// Adds two vectors element-wise.
t_tuple	*add(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*new_v;
	int		i;

	i = -1;
	if (tuple1->size != tuple2->size)
		return (NULL);
	new_v = tuple(0.0);
	if (!new_v)
		return (NULL);
	new_v->val = malloc(tuple1->size * sizeof(double));
	if (!new_v->val)
		return (NULL);
	new_v->size = tuple1->size;
	while (++i < tuple1->size)
		new_v->val[i] = tuple1->val[i] + tuple2->val[i];
	return (new_v);
}
