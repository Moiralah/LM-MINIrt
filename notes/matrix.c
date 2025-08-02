/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:40:53 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:40:54 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Creates a matrix of tuples with a specified size.
t_tuple	**matrix(int size, ...)
{
	t_tuple	**matrix;
	va_list	tuples;
	int		i;

	i = -1;
	matrix = ft_calloc(size + 1, sizeof(t_tuple *));
	if (!matrix)
		return (NULL);
	va_start(tuples, size);
	while (++i < size)
		matrix[i] = va_arg(tuples, t_tuple *);
	matrix[i] = NULL;
	return (matrix);
}

t_tuple	**copy_m(t_tuple **old)
{
	t_tuple	**new;
	int		size;
	int		i;

	i = -1;
	size = len_m(old);
	new = matrix(size);
	if (!new)
		return (NULL);
	while (++i < size)
	{
		new[i] = copy_t(old[i]);
		if (!new[i])
			return (free_m(new, i), NULL);
	}
	return (new);
}

// Returns the number of rows in a matrix.
int	len_m(t_tuple **m)
{
	int	h;

	h = 0;
	while (m && m[h])
		h++;
	return (h);
}

/* // Checks if two matrices are equal.
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
} */

// Frees the memory allocated for a matrix.
void	free_m(t_tuple **matrix, int stop)
{
	int	i;

	i = -1;
	while ((matrix[++i]) && (i < stop))
		free_t(matrix[i]);
	free(matrix);
}

// Prints the contents of a matrix.
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
		print_t(matrix[i]);
}
