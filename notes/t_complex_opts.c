/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_complex_opts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:50 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:51 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Computes the cross product of two 3D vectors.
t_tuple	*cross(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*new_v;

	if ((t1->size != 4) && (t2->size != 4))
		return (NULL);
	new_v = tuple(0.0);
	new_v->val = malloc(t1->size * sizeof(double));
	new_v->size = t1->size;
	if (!new_v)
		return (NULL);
	new_v->val[0] = (t1->val[1] * t2->val[2]) - (t2->val[1] * t1->val[2]);
	new_v->val[1] = (t2->val[0] * t1->val[2]) - (t1->val[0] * t2->val[2]);
	new_v->val[2] = (t1->val[0] * t2->val[1]) - (t2->val[0] * t1->val[1]);
	return (new_v);
}

// Computes the element-wise (Hadamard) product of two vectors.
t_tuple	*schur(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*new_v;
	int		i;

	i = -1;
	if (tuple1->size != tuple2->size)
		return (NULL);
	new_v = tuple(0.0);
	new_v->val = malloc(tuple1->size * sizeof(double));
	new_v->size = tuple1->size;
	if (!new_v)
		return (NULL);
	while (++i < tuple1->size)
		new_v->val[i] = tuple1->val[i] * tuple2->val[i];
	return (new_v);
}

// Normalizes a vector to have a magnitude of 1.
t_tuple	*norm(t_tuple *t)
{
	t_tuple	*new_v;
	double	magnitude;
	int		i;

	i = -1;
	magnitude = mag(t);
	new_v = tuple(0.0);
	new_v->val = malloc(t->size * sizeof(double));
	new_v->size = t->size;
	if (!new_v)
		return (NULL);
	while (++i < t->size)
		new_v->val[i] = t->val[i] / magnitude;
	return (new_v);
}

// Computes the magnitude (length) of a vector.
double	mag(t_tuple *tuple)
{
	double	mag;
	int		i;

	mag = 0.0;
	i = -1;
	while (++i < tuple->size)
		mag += (tuple->val[i] * tuple->val[i]);
	return (sqrt(mag));
}

// Computes the dot product of two vectors.
// Dot product = cosine of angle between them.
// Crucial for lighting, reflections, and refractions.
// It compute how light rays interact with surfaces.
double	dot(t_tuple *tuple1, t_tuple *tuple2)
{
	double	product;
	int		i;

	product = 0;
	i = -1;
	while (++i < tuple1->size)
		product += (tuple1->val[i] * tuple2->val[i]);
	return (product);
}
