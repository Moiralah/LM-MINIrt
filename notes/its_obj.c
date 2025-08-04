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

t_its	**merge_its_s(t_its **list1, t_its **list2)
{
	t_its	**merged;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if (!list1 && !list2)
		return (NULL);
	if (!list1)
		return (list2);
	else if (!list2)
		return (list1);
	while (list1[len1])
		len1++;
	while (list2[len2])
		len2++;
	merged = ft_calloc(len1 + len2 + 1, sizeof(t_its *));
	merged[len1 + len2] = NULL;
	while (--len2 >= 0)
		merged[len2 + len1] = list2[len2];
	while (--len1 >= 0)
		merged[len1] = list1[len1];
	free(list1);
	free(list2);
	return (merged);
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
	if (!its_s)
		return (NULL);
	while (its_s[i] && (its_s[i]->len <= 0))
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
