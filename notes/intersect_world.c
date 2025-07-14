#include "minirt.h"

t_world *def_world(void)
{
	t_world *world;
	t_light *lit;
	t_sphere *s1;
	t_sphere *s2;

	world = malloc(sizeof(t_world));
	if(!world)
		return(NULL);

	lit = light(tuple(4, -10.0, 10.0, -10.0), rgb_hex(1,1,1));
	world->light = lit;

	s1 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), material(rgb_hex(0.8, 1.0, 0.6), tuple(4, 0.7, 0.7, 0.7, 1.0)), 1.0);
	s2 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), material(rgb_hex(1.0, 1.0, 1.0), tuple(4, 0.7, 0.7, 0.7, 1.0)), 0.5);
	s2->t_matrix = scale(4, 0.5, 0.5, 0.5);

	world->object = ft_calloc(3, sizeof(t_obj *));
	world->object[1] = object(s1, 'S');
	world->object[2] = object(s2, 'S');
	world->object[3] = NULL;

	return(world);
}

t_its **intsect_world(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	**temp;
	int		i;

	intersections = ft_calloc(1, sizeof(t_its));
	if (!intersections)
		return(NULL);

	i = -1;
	while (world->object[++i])
	{
		temp = its_s(world->object[i], ray);
		if (temp)
			intersections = merge(intersections, temp);
	}

	return(intersections);
}

void test_intersect_world(void)
{
	t_world *world = def_world();
	t_ray *rays = ray(tuple(4, 0.0, 0.0, -5.0, 1.0), tuple(4, 0.0, 0.0, 1.0, 0.0));
	t_its **intersections = intsect_world(world, rays);

	// Print intersections
	for (int i = 0; intersections[i]; i++)
		printf("Intersection t: %f\n", intersections[i]->len[0]);

	// free_its_s(intersections);
	// free_ray(rays);
	// free_world(world);
}
