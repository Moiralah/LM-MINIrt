/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_basic_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:40:10 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:40:11 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Multiplies two matrices.
t_tuple	**mxm(t_tuple **m1, t_tuple **m2)
{
	t_tuple	**new_m;
	t_tuple	**trans;
	int		h;
	int		w;
	int		i;

	h = len_m(m1);
	w = m2[0]->size;
	new_m = matrix(h);
	if (!new_m)
		return (NULL);
	trans = transpose(m2);
	if (!trans)
		return (free(new_m), NULL);
	while (--h >= 0)
	{
		new_m[h] = tuple(w);
		if (!new_m[h])
			return (free_m(trans, len_m(trans)), free_m(new_m, h), NULL);
		i = -1;
		while (++i < w)
			new_m[h]->val[i] = dot(m1[h], trans[i]);
	}
	return (free_m(trans, len_m(trans)), new_m);
}

// Multiplies each element of a matrix by a scalar value.
void	mult_m(t_tuple **m, double value)
{
	t_tuple	*product;
	int		row;

	row = -1;
	while (m[++row])
	{
		product = mult(m[row], value);
		free_t(m[row]);
		m[row] = product;
	}
}
