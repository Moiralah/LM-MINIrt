/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:42:02 by huidris           #+#    #+#             */
/*   Updated: 2025/08/07 04:46:55 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Converts a string to a floating-point number.
float	ft_atof(const char *str)
{
	char	**numint;
	float	num;
	float	fraction;
	int		sign;
	int		len;

	sign = 1;
	if (str[0] == '-')
		sign = -1;
	numint = ft_split(str, '.');
	if (!numint || !numint[0])
		return (0.0f);
	num = fabs((float)ft_atoi(numint[0]));
	fraction = 0.0f;
	if (numint[1])
	{
		len = 0;
		while (numint[1][len] >= '0' && numint[1][len] <= '9')
			len++;
		fraction = ft_atoi(numint[1]) / powf(10, len);
	}
	free2d(numint);
	return (sign * (num + fraction));
}

// Creates a tuple with a specified size and values.
t_tuple	*tuple(int size, ...)
{
	t_tuple	*new_t;
	va_list	doubles;
	int		i;

	new_t = ft_calloc(1, sizeof(t_tuple));
	if (!new_t)
		return (NULL);
	new_t->val = NULL;
	if (size)
	{
		new_t->val = ft_calloc(size, sizeof(double));
		if (!new_t->val)
			return (NULL);
	}
	va_start(doubles, size);
	i = -1;
	while (++i < size)
		new_t->val[i] = va_arg(doubles, double);
	new_t->size = size;
	va_end(doubles);
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
	new->val = ft_calloc(1, size * sizeof(double));
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
