#include "minirt.h"

t_tuple	**matrix(int size, ...)
{
	t_tuple	**matrix;
	va_list	tuples;
	int		i;

	i = -1;
	matrix = calloc(size, sizeof(t_tuple *));
	if (!matrix)
		return (NULL);
	va_start(tuples, size);
	while (++i < (size - 1))
		matrix[i] = va_arg(tuples, t_tuple *);
	matrix[i] = NULL;
	return (matrix);
}

int	len_m(t_tuple **m)
{
	int	h;

	h = 0;
	while (m[h])
		h++;
	return (h);
}

int	equal_m(t_tuple **m1, t_tuple **m2)
{
	int	w;
	int	h;

	if (len_m(m1) != len_m(m2))
		return (0);
	if (m1[0]->size != m2[0]->size)
		return (0);
	h = len_m(m1);
	while (--h >= 0)
	{
		w = m1[0]->size - 1;
		while ((w >= 0) && (m1[h]->val[w] == m2[h]->val[w]))
			w--;
		if (w < 0)
			return (0);
	}
	return (1);
}

void	free_m(t_tuple **matrix, int stop)
{
	int	i;

	i = -1;
	while ((matrix[++i]) && (i < stop))
		free_t(matrix[i]);
	free(matrix);
}

void	print_m(t_tuple **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
	{
		printf("(null)\n");
		return ;
	}
	while (matrix[++i])
		print_t(matrix[i]->val, matrix[i]->size);
}
