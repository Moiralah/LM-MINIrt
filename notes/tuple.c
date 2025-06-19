#include <stdio.h>
#include "minirt.h"

float	ft_atof(const char *str)
{
	char	**numint;
	float	num;
	float	fraction;
	int		i;

	numint = ft_split(str, '.');
	num = 0.0f + ft_atoi(numint[0]);
	i = 0;
	fraction = 1.0f;
	if (numint[1] == NULL)
		return (num);
	while (numint[1][i] >= '0' && numint[1][i] <= '9')
	{
		fraction /= 10.0f;
		num += (numint[1][i++] - '0') * fraction;
	}
	return (num);
}

t_tuple	*tuple(int size, ...)
{
	t_tuple	*new_t;
	va_list	doubles;
	int		i;

	new_t = calloc(1, sizeof(t_tuple));
	if (!new_t)
		return (NULL);
	new_t->val = NULL;
	if (size)
		new_t->val = calloc(size, sizeof(double));
	va_start(doubles, size);
	i = -1;
	while (++i < size)
		new_t->val[i] = va_arg(doubles, double);
	new_t->size = size;
	new_t->next = NULL;
	return (new_t);
}

void	free_t(t_tuple *tuple)
{
	free(tuple->val);
	free(tuple);
}

void	print_t(double *vector, int size)
{
	int	i;

	i = -1;
	if (!vector)
	{
		printf("(null)\n");
		return ;
	}
	printf("[");
	while (++i < (size - 1))
		printf("%f ", vector[i]);
	printf("%f]\n", vector[i]);
}
