/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:24 by huidris           #+#    #+#             */
/*   Updated: 2025/08/02 18:04:35 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_comps	*prepare_computations(t_its *intersection, t_ray *ray)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	comps->t = intersection->len;
	comps->obj = intersection->obj;
	comps->point = travel(ray, comps->t);
	comps->eyev = mult(ray->dir, -1.0);
	comps->normalv = normal_at(comps->obj, comps->point);
	comps->over_point = add(comps->point, mult(comps->normalv, EPSILON));
	comps->inside = false;
	if (dot(comps->normalv, comps->eyev) >= 0)
		return (comps);
	comps->inside = true;
	comps->normalv = mult(comps->normalv, -1.0);
	return (comps);
}

void	free_comps(t_comps *comps)
{
	if (!comps)
		return ;
	free_t(comps->point);
	free_t(comps->eyev);
	free_t(comps->normalv);
	free(comps);
}
