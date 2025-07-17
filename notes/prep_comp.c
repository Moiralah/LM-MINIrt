// #include "minirt.h"

// t_comps *prepare_computations(t_its *intersection, t_ray *ray)
// {
// 	t_comps *comps;

// 	comps = malloc(sizeof(t_comps));
// 	if (!comps)
// 		return (NULL);

// 	comps->t = intersection->len[0];
// 	comps->obj = intersection->obj;
// 	comps->point = travel(ray, comps->t);
// 	comps->eyev = mult(ray->dir, -1);
// 	comps->normalv = normal_at(comps->obj, comps->point);

// 	if (dot(comps->normalv, comps->eyev) < 0)
// 	{
// 		comps->inside = true;
// 		comps->normalv = mult(comps->normalv, -1.0);
// 	}
// 	else
// 		comps->inside = false;
// 	return (comps);
// }
