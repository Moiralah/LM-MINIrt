#include "minirt.h"

t_comps	*prepare_computations(t_its *intersection, t_ray *ray)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	comps->t = intersection->len[0];
	comps->obj = intersection->obj;
	comps->point = travel(ray, comps->t);
	comps->eyev = mult(ray->dir, -1);
	comps->normalv = normal_at(comps->obj, comps->point);
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = mult(comps->normalv, -1.0);
	}
	else
		comps->inside = false;
	return (comps);
}

int	shade_hit(t_world *world, t_comps *comps)
{
	int	colour;

	colour = lighting(get_obj_mat(comps->obj), world->light,
			matrix(4.0, comps->point, comps->eyev, comps->normalv));
	return (colour);
}

int	color_at(t_world *world, t_ray *ray)
{
	t_its	**intersection;
	t_its	*hits;
	t_comps	*comps;
	int		color;

	intersection = intsect_world(world, ray);
	hits = hit(intersection);
	if (!hits)
	{
		free_its_s(intersection);
		return (rgb_hex(0, 0, 0));
	}
	comps = prepare_computations(hits, ray);
	color = shade_hit(world, comps);
	free_its_s(intersection);
	free_comps(comps);
	return (color);
}

void	free_comps(t_comps *comps)
{
	if (comps)
	{
		free_t(comps->point);
		free_t(comps->eyev);
		free_t(comps->normalv);
		free(comps);
	}
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
	v[LEFT] = cross(v[UPNORM], v[FORWARD]);
	v[TRUEUP] = cross(v[LEFT], v[FORWARD]);
	orientation = matrix(4.0,
			v[LEFT]->val[0], v[LEFT]->val[1], v[LEFT]->val[2], 0,
			v[TRUEUP]->val[0], v[TRUEUP]->val[1], v[TRUEUP]->val[2], 0,
			-v[FORWARD]->val[0], -v[FORWARD]->val[1], -v[FORWARD]->val[2], 0,
			0, 0, 0, 1);
	translation_matrix = translate(-from->val[0], -from->val[1], -from->val[2]);
	view_matrix = mxm(orientation, translation_matrix);
	return (view_matrix);
}


