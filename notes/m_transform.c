#include "minirt.h"

t_tuple	**identity(int size)
{
	t_tuple	**id;
	int		i;
	int		q;

	i = -1;
	id = matrix(size);
	while (++i < size)
	{
		id[i] = tuple(size);
		q = -1;
		while (++q < size)
		{
			id[i]->val[q] = 0;
			if (i == q)
				id[i]->val[q] = 1;
		}
	}
	return (id);
}

t_tuple	**translate(int m_size, ...)
{
	t_tuple	**m;
	va_list	doubles;
	int		i;

	i = -1;
	va_start(doubles, m_size);
	m = identity(m_size);
	while (++i < (m_size - 1))
		m[i]->val[m_size - 1] = va_arg(doubles, double);
	return (m);
}

t_tuple	**scale(int m_size, ...)
{
	t_tuple	**s;
	va_list	doubles;
	int		i;

	i = -1;
	va_start(doubles, m_size);
	s = identity(m_size);
	while (++i < (m_size - 1))
		s[i]->val[i] = va_arg(doubles, double);
	return (s);
}

t_tuple	**rotate(int m_size, int axis, double degree)
{
	t_tuple	**r;
	int		i;
	int		q;

	i = -1;
	q = axis;
	r = identity(m_size);
	while (++i < (m_size - 1))
	{
		if (i == axis)
			continue ;
		r[i]->val[i] = cos(degree);
		r[i]->val[(m_size - 1) - i - axis] = sin(degree) * pow(-1, ++q);
	}
	return (r);
}

t_tuple	**shear(t_tuple **ori_matrix, int axis, ...)
{
	t_tuple	**sheared;
	t_tuple	**id;
	va_list	vals;
	int	size;
	int	i;

	i = -1;
	size = ori_matrix[0]->size;
	id = identity(size);
	va_start(vals, axis);
	while (++i < (size - 1))
	{
		if (i == axis)
			continue;
		id[axis]->val[i] = va_arg(vals, double);
	}
	sheared = mxm(ori_matrix, id);
	free_m(id, size);
	return (sheared);
}
