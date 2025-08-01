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
