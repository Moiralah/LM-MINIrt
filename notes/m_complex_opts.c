/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_complex_opts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:40:19 by huidris           #+#    #+#             */
/*   Updated: 2025/08/04 00:51:50 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	split(t_tuple **m, t_tuple **mnrs)
{
	t_tuple	**mnr;
	int		row;
	int		col;

	row = -1;
	while (m[++row])
	{
		mnrs[row] = tuple(m[row]->size);
		if (!mnrs[row])
			continue ;
		col = -1;
		while (++col < m[row]->size)
		{
			mnr = subm(m, row, col);
			if (!mnr)
				continue ;
			mnrs[row]->val[col] = det(mnr, len_m(mnr)) * pow(-1, row + col);
			free_m(mnr, len_m(mnr));
		}
	}
}

// Calculates the inverse of a matrix.
t_tuple	**inverse(t_tuple **m)
{
	t_tuple	**trans;
	t_tuple	**mnrs;
	int		len;

	len = len_m(m);
	if (!det(m, len))
		return (NULL);
	mnrs = matrix(len);
	if (!mnrs)
		return (NULL);
	split(m, mnrs);
	trans = transpose(mnrs);
	if (!trans)
		return (free_m(mnrs, len_m(mnrs)), NULL);
	mult_m(trans, 1 / det(m, len));
	return (free_m(mnrs, len_m(mnrs)), trans);
}

// Creates a submatrix by removing a specified row and column.
t_tuple	**subm(t_tuple **m, int row, int col)
{
	t_tuple	**new_m;
	int		i[4];

	i[0] = len_m(m);
	i[1] = i[0] - 1;
	new_m = matrix(i[0] - 1);
	if (!new_m)
		return (NULL);
	while (--i[0] >= 0)
	{
		if (i[0] == row)
			continue ;
		new_m[--i[1]] = tuple(m[0]->size - 1);
		if (!new_m[i[1]])
			return (free_m(new_m, i[1]), NULL);
		i[2] = -1;
		i[3] = -1;
		while (++i[2] < m[0]->size)
		{
			if (i[2] == col)
				continue ;
			new_m[i[1]]->val[++i[3]] = m[i[0]]->val[i[2]];
		}
	}
	return (new_m);
}

// Transposes a matrix.
t_tuple	**transpose(t_tuple **m)
{
	t_tuple	**new_m;
	int		len;
	int		h;
	int		w;

	w = m[0]->size;
	len = len_m(m);
	new_m = matrix(w);
	if (!new_m)
		return (NULL);
	while (--w >= 0)
	{
		h = len;
		new_m[w] = tuple(0);
		if (!new_m[w])
			return (free_m(new_m, w), NULL);
		new_m[w]->val = ft_calloc(h, sizeof(double));
		new_m[w]->size = h;
		while (--h >= 0)
			new_m[w]->val[h] = m[h]->val[w];
	}
	return (new_m);
}

// Calculates the determinant of a matrix.
double	det(t_tuple **m, int ori_size)
{
	double	total;
	double	ad;
	double	bc;
	int		len;
	int		col;

	total = 0.0;
	col = -1;
	if (!m)
		return (0.0);
	len = len_m(m);
	while ((len > 2) && (++col < len))
		total += m[0]->val[col] * det(subm(m, 0, col), ori_size) * pow(-1, col);
	if (len == ori_size)
		return (total);
	else if (len > 2)
		return (free_m(m, len), total);
	ad = m[0]->val[0] * m[1]->val[1];
	bc = m[0]->val[1] * m[1]->val[0];
	free_m(m, len);
	return (ad - bc);
}
