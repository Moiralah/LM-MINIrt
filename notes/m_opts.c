#include "minirt.h"

t_tuple	**mult_m(t_tuple **m1, t_tuple **m2)
{
	t_tuple	**new_m;
	int		h;
	int		w;
	int		i;

	h = 0;
	while (m1[h])
		h++;
	w = m2[0]->size;
	new_m = matrix(h);
	if (!new_m)
		return (NULL);
	transpose(m2);
	while (--h >= 0)
	{
		new_m[h] = tuple(w);
		if (!new_m[h])
			return (NULL);
		i = -1;
		while (++i < w)
			new_m[h]->val[i] = dot(m1[h]->val, m2[i]->val, m1[0]->size);
	}
	return (new_m);
}

t_tuple	**submatrix(t_tuple **m, int row, int col)
{
	t_tuple	**new_m;
	int		i[4];

	i[0] = 0;
	while (m[i[0]])
		i[0]++;
	i[1] = i[0] - 1;
	new_m = matrix(i[0]);
	while (--i[0] >= 0)
	{
		if (i[0] == row)
			continue ;
		new_m[--i[1]] = tuple(m[0]->size - 1);
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

double	det(t_tuple **m, int size)
{
	double	total;
	double	ad;
	double	bc;
	int		col;

	total = 0;
	col = -1;
	while ((size > 2) && (++col < size))
		total += m[0]->val[col] * det(submatrix(m, 0, col), size - 1);
	if (size > 2)
		return (total);
	ad = m[0]->val[0] * m[1]->val[1];
	bc = m[0]->val[1] * m[1]->val[0];
	return (ad - bc);
}

void	transpose(t_tuple **m)
{
	double	prev;
	int		i;
	int		q;

	i = -1;
	while (m[++i])
	{
		q = i;
		while (++q < m[i]->size)
		{
			prev = m[i]->val[q];
			m[i]->val[q] = m[q]->val[i];
			m[q]->val[i] = prev;
		}
	}
}
