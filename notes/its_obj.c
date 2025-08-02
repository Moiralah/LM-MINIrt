/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:40:04 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 17:25:25 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Creates a list of intersections for a given size.
t_its	**its_s(int size, ...)
{
	t_its	**its_list;
	va_list	its_s;
	int		i;

	i = -1;
	its_list = ft_calloc(size + 1, sizeof(t_its *));
	if (!its_list)
		return (NULL);
	va_start(its_s, size);
	while (++i < size)
		its_list[i] = va_arg(its_s, t_its *);
	its_list[i] = NULL;
	va_end(its_s);
	return (merge(its_list, i));
}

// Creates a new intersection object.
t_its	*its(t_obj *obj, double len_from_ori)
{
	t_its	*new_its;

	new_its = ft_calloc(1, sizeof(t_its));
	if (!new_its)
		return (NULL);
	new_its->obj = obj;
	new_its->len = len_from_ori;
	return (new_its);
}

// Finds the first positive intersection (hit).
t_its	*hit(t_its **its_s)
{
	int	i;

	i = 0;
	while (its_s && its_s[i] && (its_s[i]->len <= 0))
		i++;
	return (its_s[i]);
}

// Frees the memory allocated for a list of intersections.
void	free_its_s(t_its **its_s)
{
	int	i;

	i = -1;
	while (its_s[++i])
		free(its_s[i]);
	free(its_s);
}
