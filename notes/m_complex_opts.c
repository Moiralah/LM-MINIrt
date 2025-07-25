#include "minirt.h"

// Multiplies two matrices.
t_tuple	**mxm(t_tuple **m1, t_tuple **m2)
{
	t_tuple	**new_m;
	int		h;
	int		w;
	int		i;

	h = len_m(m1);
	w = m2[0]->size;
	new_m = matrix(h);
	if (!new_m)
		return (NULL);
	m2 = transpose(m2);
	while (--h >= 0)
	{
		new_m[h] = tuple(w);
		if (!new_m[h])
			return (free_m(new_m, h), NULL);
		i = -1;
		while (++i < w)
			new_m[h]->val[i] = dot(m1[h], m2[i]);
	}
	return (new_m);
}

// Calculates the inverse of a matrix.
t_tuple	**inverse(t_tuple **m)
{
	t_tuple	**mnrs;
	t_tuple	**mnr;
	int		row;
	int		col;

	if (!det(m, len_m(m)))
		return (NULL);
	row = -1;
	mnrs = matrix(len_m(m));
	if (!mnrs)
		return (NULL);
	while (m[++row])
	{
		mnrs[row] = tuple(m[row]->size);
		col = -1;
		while (++col < m[row]->size)
		{
			mnr = subm(m, row, col);
			mnrs[row]->val[col] = det(mnr, len_m(mnr)) * pow(-1, row + col);
			free_m(mnr, len_m(mnr));
		}
	}
	mnrs = transpose(mnrs);
	mult_m(mnrs, 1 / det(m, len_m(m)));
	return (mnrs);
}

// Creates a submatrix by removing a specified row and column.
t_tuple	**subm(t_tuple **m, int row, int col)
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
	int		h;
	int		w;

	w = m[0]->size;
	new_m = matrix(w + 1);
	while (--w >= 0)
	{
		h = len_m(m);
		new_m[w] = tuple(0);
		new_m[w]->val = malloc(h * sizeof(double));
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
	int		col;

	total = 0;
	col = -1;
	while ((len_m(m) > 2) && (++col < len_m(m)))
		total += m[0]->val[col] * det(subm(m, 0, col), ori_size) * pow(-1, col);
	if (len_m(m) == ori_size)
		return (total);
	else if (len_m(m) > 2)
		return (free_m(m, len_m(m)), total);
	ad = m[0]->val[0] * m[1]->val[1];
	bc = m[0]->val[1] * m[1]->val[0];
	free_m(m, len_m(m));
	return (ad - bc);
}
