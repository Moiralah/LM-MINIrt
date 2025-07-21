#include "minirt.h"

// Computes the intersections of a ray with a sphere.
/* t_its	*sphere_its(t_ray *r, t_sphere *sphere)
{
	t_obj		*obj;
	t_ray		*new_ray;
	t_tuple		*rto;
	double		*result;
	double		rtc;
	double		h;

	obj = object(sphere, 'S');
	if (!obj)
		return (NULL);
	new_ray = transform(r, inverse(sphere->t_matrix));
	rto = sub(sphere->ori, new_ray->ori);
	rtc = dot(rto, new_ray->dir);
	h = pow(mag(rto), 2) - pow(rtc, 2);
	print_t(rto);
	printf("%f | %f\n", rtc, h);
	if (sqrt(h) > sphere->rad)
		return (free_t(rto), its(obj, NULL, 0));
	h = pow(mag(rto), 2) - pow(rtc, 2);
	result = calloc(2, sizeof(double));
	if (!result)
		return (free_t(rto), free(obj), NULL);
	h = sqrt(pow(sphere->rad, 2) - h);
	result[0] = rtc - h;
	result[1] = rtc + h;
	if (result[0] == result[1])
		return (free_t(rto), its(obj, result, 1));
	return (free_t(rto), its(obj, result, 2));
} */

t_its	*sphere_its(t_ray *r, t_sphere *sphere)
{
	t_obj		*obj;
	t_ray		*new_ray;
	t_tuple		*rto;
	double		values[4];
	double		*result;

	result = malloc(2 * sizeof(double));
	if (!result)
		return (NULL);
	obj = object(sphere, 'S');
	if (!obj)
		return (NULL);
	new_ray = transform(r, inverse(sphere->t_matrix));
	if (!new_ray)
		return (free(result), free(obj), NULL);
	rto = sub(new_ray->ori, sphere->ori);
	if (!rto)
		return (free(obj), NULL);
	values[0] = dot(new_ray->dir, new_ray->dir);
	values[1] = 2 * dot(new_ray->dir, rto);
	values[2] = dot(rto, rto) - 1;
	values[3] = pow(values[1], 2) - (4 * values[0] * values[2]);
	if (values[3] < 0)
		return (free_t(rto), its(obj, NULL, 0));
	result[0] = (-values[1] - sqrt(values[3])) / (2 * values[0]);
	result[1] = (-values[1] + sqrt(values[3])) / (2 * values[0]);
	if (result[0] == result[1])
		return (free_t(rto), its(obj, result, 1));
	return (free_t(rto), its(obj, result, 2));
}
