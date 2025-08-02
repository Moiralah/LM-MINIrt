/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:24 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 22:55:10 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	initialise_tuples(t_comps *comps, t_ray *ray)
{
	comps->point = travel(ray, comps->t);
	if (!comps->point)
		return (0);
	comps->eyev = mult(ray->dir, -1.0);
	if (!comps->eyev)
		return (free_t(comps->point), 0);
	comps->normalv = normal_at(comps->obj, comps->point);
	if (!comps->normalv)
		return (free_t(comps->point), free_t(comps->eyev), 0);
	comps->over_point = add(comps->point, mult(comps->normalv, EPSILON));
	if (!comps->over_point)
	{
		free_t(comps->point);
		free_t(comps->eyev);
		free_t(comps->normalv);
		return (0);
	}
	return (1);
}

t_comps	*prepare_computations(t_its *intersection, t_ray *ray)
{
	t_comps	*comps;
	t_tuple	*temp;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	comps->t = intersection->len;
	comps->obj = intersection->obj;
	comps->inside = false;
	if (!initialise_tuples(comps, ray))
		return (free(comps), NULL);
	if (dot(comps->normalv, comps->eyev) >= 0)
		return (comps);
	comps->inside = true;
	temp = comps->normalv;
	comps->normalv = mult(comps->normalv, -1.0);
	free_t(temp);
	if (!comps->normalv)
	{
		free_t(comps->point);
		free_t(comps->eyev);
		free_t(comps->normalv);
		return (free_t(comps->over_point), free(comps), NULL);
	}
	return (comps);
}

void	free_comps(t_comps *comps)
{
	free_t(comps->point);
	free_t(comps->eyev);
	free_t(comps->normalv);
	free_t(comps->over_point);
	free(comps);
}
