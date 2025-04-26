#include "minirt.h"

t_tuple	**matrix(int size, ...)
{
	t_tuple	**matrix;
	va_list	tuples;
	int		i;

	i = -1;
	matrix = calloc(size, sizeof(t_tuple *));
	va_start(tuples, size);
	while (++i < (size - 1))
		matrix[i] = va_arg(tuples, t_tuple *);
	matrix[i] = NULL;
	return (matrix);
}

int	equal_m(t_tuple **m1, t_tuple **m2)
{
	int	width;
	int	height;
	int	i;

	height = 0;
	width = m1[0]->size;
	while (m1[height] && m2[height])
	{
		if ((m1[height]->size != width) || (m2[height]->size != width))
			return (0);
		height++;
	}
	if (m1[height] != m2[height])
		return (0);
	while (--height >= 0)
	{
		i = width - 1;
		while ((i >= 0) && (m1[height]->val[i] == m2[height]->val[i]))
			i--;
		if (i < 0)
			return (0);
	}
	return (1);
}

void	free_m(t_tuple **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free_t(matrix[i]);
	free(matrix);
}

void	print_m(t_tuple **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		print_t(matrix[i]->val, matrix[i]->size);
}
