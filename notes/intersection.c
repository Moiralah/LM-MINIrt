/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:40:00 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:40:01 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_its	**plane_its(t_obj *obj, t_ray *ray)
{
	t_tuple	**inv;
	t_tuple	*origin;
	t_tuple	*dir;
	double	t;

	inv = inverse(get_obj_tf(obj));
	origin = transform_ori(inv, ray->ori);
	dir = transform_dir(inv, ray->dir);
	if (fabs(dir->val[1]) < __DBL_EPSILON__)
		return (NULL);
	t = -origin->val[1] / dir->val[1];
	return (its_s(1, its(obj, t)));
}

// Computes the intersections of a ray with a sphere.
t_its	**sphere_its(t_obj *obj, t_ray *r)
{
	t_tuple		*rto;
	double		values[4];
	double		result[2];

	rto = sub(r->ori, get_obj_ori(obj));
	values[0] = dot(r->dir, r->dir);
	values[1] = 2 * dot(r->dir, rto);
	values[2] = dot(rto, rto) - 1;
	values[3] = pow(values[1], 2) - (4 * values[0] * values[2]);
	if (values[3] < 0)
		return (free_t(rto), NULL);
	result[0] = (-values[1] - sqrt(values[3])) / (2 * values[0]);
	result[1] = (-values[1] + sqrt(values[3])) / (2 * values[0]);
	if (result[0] == result[1])
		return (free_t(rto), its_s(1, its(obj, result[0])));
	return (free_t(rto), its_s(2, its(obj, result[0]), its(obj, result[1])));
}

t_its	**check_cap(t_obj *obj, t_cylinder *cy, t_ray *r)
{
	t_its		**caps[2];
	t_tuple		*hit;
	double		t;

	caps[0] = NULL;
	caps[1] = NULL;
	t = (cy->min - r->ori->val[1]) / r->dir->val[1]; 
	hit = travel(r, t);
	if ((pow(hit->val[0], 2) + pow(hit->val[2], 2)) <= 1)
		caps[0] = its_s(1, its(obj, t));
	t = (cy->max - r->ori->val[1]) / r->dir->val[1]; 
	free_t(hit);
	hit = travel(r, t);
	if ((pow(hit->val[0], 2) + pow(hit->val[2], 2)) <= 1)
		caps[1] = its_s(1, its(obj, t));
	free_t(hit);
	caps[0] = merge_its_s(caps[0], caps[1]);
	return (caps[0]);
}

t_its	**cylinder_its(t_obj *obj, t_ray *r)
{
	t_its		**hits;
	t_cylinder	*cy;
	t_tuple		*hit[2];
	double		values[4];
	double		len[2];

	cy = (t_cylinder *)(obj->data);
	values[0] = pow(r->dir->val[0], 2) + pow(r->dir->val[2], 2);
	if ((values[0] == 0) && (cy->closed))
		return (check_cap(obj, cy, r));
	else if (values[0] == 0)
		return (NULL);
	values[1] = (2 * r->ori->val[0] * r->dir->val[0]);
	values[1] += (2 * r->ori->val[2] * r->dir->val[2]);
	values[2] = pow(r->ori->val[0], 2) + pow(r->ori->val[2], 2) - 1;
	values[3] = pow(values[1], 2) - (4 * values[0] * values[2]);
	if (values[3] < 0)
		return (NULL);
	len[0] = (-values[1] - sqrt(values[3])) / (2 * values[0]);
	len[1] = (-values[1] + sqrt(values[3])) / (2 * values[0]);
	double	temp;
	if (len[0] > len[1])
	{
		temp = len[0];
		len[0] = len[1];
		len[1] = temp;
	}
	hit[0] = travel(r, len[0]);
	hit[1] = travel(r, len[1]);
	hits = NULL;
	if (cy->closed)
		hits = check_cap(obj, cy, r);
	if ((hit[0]->val[1] > cy->min) && (hit[0]->val[1] < cy->max))
		hits = merge_its_s(its_s(1, its(obj, len[0])), hits);
	if ((hit[1]->val[1] > cy->min) && (hit[1]->val[1] < cy->max))
		hits = merge_its_s(its_s(1, its(obj, len[1])), hits);
	return (hits);
}

t_its	**calculate_its(t_obj *obj, t_ray *r)
{
	t_ray		*new_ray;
	t_tuple		**inverse_m;
	t_tuple		*ray_values[2];

	inverse_m = inverse(get_obj_tf(obj));
	if (!inverse_m)
		return (NULL);
	ray_values[0] = transform_ori(inverse_m, r->ori);
	if (!ray_values[0])
		return (free_m(inverse_m, len_m(inverse_m)), free(obj), NULL);
	ray_values[1] = transform_dir(inverse_m, r->dir);
	if (!ray_values[1])
		return (free_m(inverse_m, len_m(inverse_m)), free(obj), NULL);
	new_ray = ray(ray_values[0], ray_values[1]);
	if (!new_ray)
		return (free_m(inverse_m, len_m(inverse_m)), free(obj), NULL);
	if (obj->type == 'S')
		return (sphere_its(obj, new_ray));
	else if (obj->type == 'P')
		return (plane_its(obj, new_ray));
	else if (obj->type == 'C')
		return (cylinder_its(obj, new_ray));
	return (NULL);
}
