#include "minirt.h"

t_tuple *eye(t_ray *ray)
{
	return (mult(ray->dir->val, -1.0, 4));
}

t_tuple *light(t_tuple *light_pos, t_tuple *point_pos)
{
	return(sub(light_pos->val, point_pos->val, 4));
}

t_tuple *normal_at(t_sphere *sphere, t_tuple *world_point)
{
	t_tuple *object;
	t_tuple *world_normal;

	object = inverse(transform(sphere)) * world_point;
	object = object->val - (4, 0, 0, 0);
	world_normal = transpose(inverse(transform(sphere))) * object->val;
	world_normal->val[3] = 0.0;
	norm(world_normal->val, 4);
	return (world_normal);
}

