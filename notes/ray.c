/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:37 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:38 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Creates a ray with an origin and direction.
t_ray	*ray(t_tuple *origin, t_tuple *direction)
{
	t_ray	*new_ray;

	new_ray = calloc(1, sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->ori = origin;
	new_ray->dir = direction;
	return (new_ray);
}

t_ray	*copy_ray(t_ray *old)
{
	t_ray	*new;
	t_tuple	*new_ori;
	t_tuple	*new_dir;

	new_ori = copy_t(old->ori);
	if (!new_ori)
		return (NULL);
	new_dir = copy_t(old->dir);
	if (!new_dir)
		return (NULL);
	new = ray(new_ori, new_dir);
	return (new);
}

// Frees the memory allocated for a ray.
void	free_ray(t_ray *ray)
{
	free_t(ray->ori);
	free_t(ray->dir);
	free(ray);
}
