#include "minirt.h"

// Creates an identity matrix of a given size.
t_tuple	**identity(int size)
{
	t_tuple	**id;
	int		i;
	int		q;

	i = -1;
	id = matrix(size);
	if (!id)
		return (NULL);
	while (++i < size)
	{
		id[i] = tuple(size);
		if (!id[i])
			return (free_m(id, i), NULL);
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

// Creates a translation matrix.
t_tuple	**translate(int m_size, ...)
{
	t_tuple	**m;
	va_list	doubles;
	int		i;

	i = -1;
	va_start(doubles, m_size);
	m = identity(m_size);
	if (!m)
		return (NULL);
	while (++i < (m_size - 1))
		m[i]->val[m_size - 1] = va_arg(doubles, double);
	return (m);
}

// Creates a scaling matrix.
t_tuple	**scale(int m_size, ...)
{
	t_tuple	**s;
	va_list	doubles;
	int		i;

	i = -1;
	va_start(doubles, m_size);
	s = identity(m_size);
	if (!s)
		return (NULL);
	while (++i < (m_size - 1))
		s[i]->val[i] = va_arg(doubles, double);
	return (s);
}

// Creates a rotation matrix for a given axis and angle.
t_tuple	**rotate(int m_size, int axis, double degree)
{
	t_tuple	**r;
	int		i;
	int		q;

	i = -1;
	q = axis;
	r = identity(m_size);
	if (!r)
		return (NULL);
	while (++i < (m_size - 1))
	{
		if (i == axis)
			continue ;
		r[i]->val[i] = cos(degree);
		r[i]->val[(m_size - 1) - i - axis] = sin(degree) * pow(-1, ++q);
	}
	return (r);
}

// Applies a shear transformation to a matrix.
t_tuple	**shear(t_tuple **ori_matrix, int axis, ...)
{
	t_tuple	**id;
	va_list	vals;
	int		size;
	int		i;

	i = -1;
	size = ori_matrix[0]->size;
	id = identity(size);
	if (!id)
		return (NULL);
	va_start(vals, axis);
	while (++i < (size - 1))
	{
		if (i == axis)
			continue ;
		id[axis]->val[i] = va_arg(vals, double);
	}
	return (id);
}
