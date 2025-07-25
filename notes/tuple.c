#include <stdio.h>
#include "minirt.h"

// Converts a string to a floating-point number.
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

// Creates a tuple with a specified size and values.
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
	return (new_t);
}

t_tuple	*copy_t(t_tuple *old)
{
	t_tuple	*new;
	int		size;

	size = old->size;
	new = tuple(0);
	if (!new)
		return (NULL);
	new->val = malloc(size * sizeof(double));
	if (!new->val)
		return (free(new), NULL);
	while (--size >= 0)
		new->val[size] = old->val[size];
	new->size = old->size;
	return (new);
}

// Frees the memory allocated for a tuple.
void	free_t(t_tuple *tuple)
{
	free(tuple->val);
	free(tuple);
}

// Prints the contents of a tuple.
void	print_t(t_tuple *vector)
{
	int	i;

	i = -1;
	if (!vector)
	{
		printf("(null)\n");
		return ;
	}
	printf("[");
	while (++i < (vector->size - 1))
		printf("%f ", vector->val[i]);
	printf("%f]\n", vector->val[i]);
}
