/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:44 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 22:05:27 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat	*material(t_tuple *color, t_tuple *values)
{
	t_mat	*material;

	material = ft_calloc(1, sizeof(t_mat));
	if (!material)
		return (NULL);
	material->color = color;
	material->ambient = values->val[0];
	material->diffuse = values->val[1];
	material->specular = values->val[2];
	material->shininess = values->val[3];
	return (material);
}

t_mat	*copy_mat(t_mat *old)
{
	t_mat	*new;

	new = ft_calloc(1, sizeof(t_mat));
	if (!new)
		return (NULL);
	new->color = copy_t(old->color);
	new->ambient = old->ambient;
	new->diffuse = old->diffuse;
	new->specular = old->specular;
	new->shininess = old->shininess;
	return (new);
}

void	free_mat(t_mat *material)
{
	free_t(material->color);
	free(material);
}
