#include "minirt.h"

t_world *def_world(void)
{
	t_world *world;
	t_light *lit;
	t_sphere *s1;
	t_sphere *s2;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);

	lit = light(tuple(4, -10.0, 10.0, -10.0, 1.0), rgb_hex(1, 1, 1));
	world->light = lit;

	s1 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), material(rgb_hex(0.8, 1.0, 0.6), tuple(4, 0.0, 0.7, 0.2, 0.0)), 1.0);
	s2 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), material(rgb_hex(1.0, 1.0, 1.0), tuple(4, 0.0, 0.0, 0.0, 0.0)), 0.5);
	//s2->t_matrix = scale(4, 0.5, 0.5, 0.5);

	world->object = ft_calloc(3, sizeof(t_obj *));
	world->object[0] = object(s1, 'S');
	world->object[1] = object(s2, 'S');
	world->object[2] = NULL;

	return (world);
}

t_its **add_intersection(t_its **intersections, t_its *obj_intersection, int *total_intersections)
{
	t_its **temp;
	int i;

	temp = ft_calloc(*total_intersections + 2, sizeof(t_its *));
	i = -1;
	while (++i < *total_intersections)
		temp[i] = intersections[i];
	temp[*total_intersections] = obj_intersection;
	temp[*total_intersections + 1] = NULL;

	free(intersections);
	(*total_intersections)++;
	return (temp);
}

t_its **intsect_world(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	*obj_its;
	t_its	*single;
	int total;
	int i;
	int	j;

	intersections = ft_calloc(1, sizeof(t_its *));
	total = 0;
	i = -1;
	while (world->object[++i])
	{
		obj_its = intersect(ray, world->object[i]);
		j = -1;
		while (++j < obj_its->cnt)
		{
			single = its(obj_its->obj, obj_its->len, 1);
			single->len = malloc(sizeof(double));
			single->len[0] = obj_its->len[j];
			intersections = add_intersection(intersections, single, &total);
		}
	}
	intersections = merge(intersections, total);
	return (intersections);
}

void test_intersect_world(void)
{
	t_world *world = def_world();
	t_ray *rays = ray(tuple(4, 0.0, 0.0, -5.0, 1.0), tuple(4, 0.0, 0.0, 1.0, 0.0));
	t_its **xs = intsect_world(world, rays);

	// Count intersections
	int count = 0;
	while (xs && xs[count])
		count++;

	printf("xs.count = %d\n", count);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < xs[i]->cnt; j++)
		{
			printf("xs[%d].t = %g\n", i, xs[i]->len[j]);
		}
	}
	//free_its_s(xs);
	//free_ray(rays);
}
