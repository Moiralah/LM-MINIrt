/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:40:00 by huidris           #+#    #+#             */
/*   Updated: 2025/08/03 22:37:48 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_its	**plane_its(t_obj *obj, t_ray *ray)
{
	double	t;
	/* t_tuple	**inv;
	t_tuple	*origin;
	t_tuple	*dir; */
	/* inv = get_inv_tf(obj);
	origin = transform_ori(inv, ray->ori);
	if (!origin)
		return (free_ray(ray), NULL);
	dir = transform_dir(inv, ray->dir);
	if (!dir)
		return (free_t(ori), NULL);
	if (fabs(dir->val[1]) < __DBL_EPSILON__)
		return (NULL);
	t = -origin->val[1] / dir->val[1]; */
	if (fabs(ray->dir->val[1]) < __DBL_EPSILON__)
		return (free_ray(ray), NULL);
	t = -ray->ori->val[1] / ray->dir->val[1];
	free_ray(ray);
	return (its_s(1, its(obj, t)));
}

// Computes the intersections of a ray with a sphere.
t_its	**sphere_its(t_obj *obj, t_sphere *sp, t_ray *r)
{
	t_tuple		*rto;
	double		values[4];
	double		len[2];

	rto = sub(r->ori, sp->ori);
	if (!rto)
		return (NULL);
	values[0] = dot(r->dir, r->dir);
	values[1] = 2 * dot(r->dir, rto);
	values[2] = dot(rto, rto) - 1;
	values[3] = pow(values[1], 2) - (4 * values[0] * values[2]);
	if (values[3] < 0)
		return (free_t(rto), NULL);
	len[0] = (-values[1] - sqrt(values[3])) / (2 * values[0]);
	len[1] = (-values[1] + sqrt(values[3])) / (2 * values[0]);
	free_ray(r);
	if (len[0] == len[1])
		return (free_t(rto), its_s(1, its(obj, len[0])));
	return (free_t(rto), its_s(2, its(obj, len[0]), its(obj, len[1])));
}

t_its	**its_caps(t_obj *obj, t_cylinder *cy, t_ray *r)
{
	t_its		**top;
	t_its		**bot;
	t_tuple		*hit;
	double		t;

	caps[0] = NULL;
	caps[1] = NULL;
	t = (cy->min - r->ori->val[1]) / r->dir->val[1];
	bot = NULL;
	top = NULL;
	t = (cy->min - r->ori->val[1]) / r->dir->val[1];
	hit = travel(r, t);
	if (!hit)
		return (NULL);
	if ((pow(hit->val[0], 2) + pow(hit->val[2], 2)) <= 1)
		caps[0] = its_s(1, its(obj, t));
	t = (cy->max - r->ori->val[1]) / r->dir->val[1];
		bot = its_s(1, its(obj, t));
	t = (cy->max - r->ori->val[1]) / r->dir->val[1];
	free_t(hit);
	hit = travel(r, t);
	if (!hit)
		return (NULL);
	if ((pow(hit->val[0], 2) + pow(hit->val[2], 2)) <= 1)
		top = its_s(1, its(obj, t));
	free_t(hit);
	return (merge_its_s(bot, top));
}

t_its	**its_shorten(t_obj *obj, t_cylinder *cy, t_ray *r, double *len)
{
	t_its	**hits;
	t_tuple	*hit1;
	t_tuple	*hit2;

	hits = NULL;
	hit1 = travel(r, len[0]);
	if (!hit1)
		return (NULL);
	hit2 = travel(r, len[1]);
	if (!hit1)
		return (NULL);
	if ((hit1->val[1] > cy->min) && (hit1->val[1] < cy->max))
		hits = merge_its_s(its_s(1, its(obj, len[0])), hits);
	if ((hit2->val[1] > cy->min) && (hit2->val[1] < cy->max))
		hits = merge_its_s(its_s(1, its(obj, len[1])), hits);
	free_t(hit1);
	free_t(hit2);
	return (hits);
}

t_its	**cylinder_its(t_obj *obj, t_cylinder *cy, t_ray *r)
{
	t_its		**hits;
	double		values[4];
	double		len[2];
	double		temp;

	hits = NULL;
	if (cy->closed)
		hits = its_caps(obj, cy, r);
	values[0] = pow(r->dir->val[0], 2) + pow(r->dir->val[2], 2);
	if (values[0] == 0)
		return (free_ray(r), hits);
	values[1] = (2 * r->ori->val[0] * r->dir->val[0]);
	values[1] += (2 * r->ori->val[2] * r->dir->val[2]);
	values[2] = pow(r->ori->val[0], 2) + pow(r->ori->val[2], 2) - 1;
	values[3] = pow(values[1], 2) - (4 * values[0] * values[2]);
	if (values[3] < 0)
		return (free_ray(r), hits);
	len[0] = (-values[1] - sqrt(values[3])) / (2 * values[0]);
	len[1] = (-values[1] + sqrt(values[3])) / (2 * values[0]);
	hits = merge_its_s(its_shorten(obj, cy, r, len), hits);
	return (free_ray(r), hits);
}
