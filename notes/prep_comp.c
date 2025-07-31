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
	comps->inside = false;
	if (dot(comps->normalv, comps->eyev) >= 0)
		return (comps);
	comps->inside = true;
	comps->normalv = mult(comps->normalv, -1.0);
	return (comps);
}

t_tuple	*shade_hit(t_world *world, t_comps *comps)
{
	t_tuple	**temp;
	t_tuple	*colour;
	int		i;

	temp = matrix(4, comps->point, comps->eyev, comps->normalv);
	if (!temp)
		return (NULL);
	i = 0;
	colour = lighting(get_obj_mat(comps->obj), world->light[i], temp);
	while (world->light[++i])
		colour = add(colour, lighting(get_obj_mat(comps->obj),
					world->light[i], temp));
	free_m(temp, 4);
	return (colour);
}

t_tuple	*color_at(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	*hit_its;
	t_comps	*comps;
	t_tuple	*color;

	intersections = its_world(world, ray);
	if (!intersections)
		return (tuple(3, 0.0, 0.0, 0.0));
	hit_its = hit(intersections);
	if (!hit_its)
	{
		free_its_s(intersections);
		return (tuple(3, 0.0, 0.0, 0.0));
	}
	comps = prepare_computations(hit_its, ray);
	color = shade_hit(world, comps);
	free_its_s(intersections);
	free_comps(comps);
	return (color);
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

#define FORWARD 0
#define UPNORM 1
#define LEFT 2
#define TRUEUP 3

t_tuple	**view_transform(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple	*v[4];
	t_tuple	**view_matrix;
	t_tuple	**orientation;
	t_tuple	**translation_matrix;

	v[FORWARD] = norm(sub(to, from));
	v[UPNORM] = norm(up);
	v[LEFT] = cross(v[FORWARD], v[UPNORM]);
	v[TRUEUP] = cross(v[LEFT], v[FORWARD]);
	orientation = matrix(5, v[LEFT], v[TRUEUP], mult(v[FORWARD], -1.0), NULL);
	orientation[3] = tuple(4, 0.0, 0.0, 0.0, 1.0);
	translation_matrix = translate(4, -from->val[0], -from->val[1], -from->val[2]);
	view_matrix = mxm(orientation, translation_matrix);
	return (view_matrix);
}
