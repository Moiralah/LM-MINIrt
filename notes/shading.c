/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:44 by huidris           #+#    #+#             */
/*   Updated: 2025/08/07 00:36:04 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*shade_hit(t_world *world, t_comps *comps)
{
	t_tuple	**temp;
	t_tuple	*colour;
	int		i;

	temp = matrix(3, comps->over_point, comps->eyev, comps->normalv);
	if (!temp)
		return (NULL);
	i = shadowed(world, comps->over_point);
	colour = lighting(get_obj_mat(comps->obj), world->light, temp, i);
	free(temp);
	return (colour);
}

#define LIGHTV				0
#define POINT				1
#define EYEV				2
#define NORMALV				3
#define REFLECTV			4
#define EFFECTIVE_COLOUR	5
#define AMBIENT				6
#define DIFFUSE				7
#define SPECULAR 			8

void	diff_spclr(t_mat *mat, t_light *l, t_tuple **t, double light_dot_normal)
{
	t_tuple	*rev_light;
	double	reflect_dot_eye;
	double	factor;

	rev_light = mult(t[LIGHTV], -1);
	t[DIFFUSE] = mult(t[EFFECTIVE_COLOUR], (mat->diffuse * light_dot_normal));
	t[REFLECTV] = reflect(rev_light, t[NORMALV]);
	free_t(rev_light);
	reflect_dot_eye = dot(t[REFLECTV], t[EYEV]);
	free_t(t[REFLECTV]);
	if (reflect_dot_eye <= 0)
		t[SPECULAR] = tuple(3, 0.0, 0.0, 0.0);
	else
	{
		factor = pow(reflect_dot_eye, mat->shininess);
		t[SPECULAR] = mult(l->intensity, (mat->specular * factor));
	}
}

t_tuple	*final_color(t_tuple *am, t_tuple *diff, t_tuple *spclr)
{
	t_tuple	*ad_plus_s;
	t_tuple	*a_plus_d;

	a_plus_d = add(am, diff);
	free_t(am);
	free_t(diff);
	ad_plus_s = add(a_plus_d, spclr);
	free_t(a_plus_d);
	free_t(spclr);
	return (ad_plus_s);
}

t_tuple	*lighting(t_mat *material, t_light *light, t_tuple **m, int shadowed)
{
	t_tuple	*t[9];
	t_tuple	*l_to_p;
	double	light_dot_normal;

	t[POINT] = m[0];
	t[EYEV] = m[1];
	t[NORMALV] = m[2];
	t[EFFECTIVE_COLOUR] = schur(material->color, light->intensity);
	l_to_p = sub(light->position, t[POINT]);
	t[LIGHTV] = norm(l_to_p);
	free_t(l_to_p);
	t[AMBIENT] = mult(t[EFFECTIVE_COLOUR], material->ambient);
	if (shadowed)
		return (free_t(t[EFFECTIVE_COLOUR]), free_t(t[LIGHTV]), t[AMBIENT]);
	light_dot_normal = dot(t[LIGHTV], t[NORMALV]);
	if (light_dot_normal < 0)
	{
		t[DIFFUSE] = tuple(3, 0.0, 0.0, 0.0);
		t[SPECULAR] = tuple(3, 0.0, 0.0, 0.0);
	}
	else
		diff_spclr(material, light, t, light_dot_normal);
	free_t(t[EFFECTIVE_COLOUR]);
	free_t(t[LIGHTV]);
	return (final_color(t[AMBIENT], t[DIFFUSE], t[SPECULAR]));
}

t_tuple	*color_at(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	*hit_its;
	t_comps	*comps;
	t_tuple	*color;

	intersections = its_world(world, ray);
	if (!intersections)
		return (mult(world->a_color, world->a_ratio));
	hit_its = hit(intersections);
	if (!hit_its)
	{
		free_its_s(intersections);
		return (mult(world->a_color, world->a_ratio));
	}
	comps = prepare_computations(hit_its, ray);
	free_its_s(intersections);
	if (!comps)
		return (NULL);
	color = shade_hit(world, comps);
	free_comps(comps);
	return (color);
}
