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

	lit = light(tuple(4, -10.0, 10.0, -10.0, 1.0), rgb_hex(1,1,1));
	world->light = lit;

	s1 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), material(rgb_hex(0.8, 1.0, 0.6), tuple(4, 0.7, 0.7, 0.7, 1.0)), 1.0);
	s2 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), material(rgb_hex(1.0, 1.0, 1.0), tuple(4, 0.7, 0.7, 0.7, 1.0)), 0.5);
	s2->t_matrix = scale(4, 0.5, 0.5, 0.5);

	world->object = ft_calloc(3, sizeof(t_obj *));
	world->object[0] = object(s1, 'S');
	world->object[1] = object(s2, 'S');
	world->object[2] = NULL;

	return(world);
}

t_its **intsect_world(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	**temp;
	t_its	*obj_intersection;
	int		i;
	int		total_intersections;

	intersections = ft_calloc(1, sizeof(t_its *));
	if (!intersections)
		return(NULL);

	i = -1;
	total_intersections = 0;
	while (world->object[++i])
	{
		// Intersect ray with current object
		obj_intersection = intersect(ray, world->object[i]);
		if (obj_intersection && obj_intersection->cnt > 0)
		{
			// Create a temporary array with this intersection
			temp = ft_calloc(2, sizeof(t_its *));
			temp[0] = obj_intersection;
			temp[1] = NULL;

			// Merge with existing intersections
			if (total_intersections == 0)
			{
				free(intersections);
				intersections = temp;
			}
			else
			{
				// Count current intersections
				int current_count = 0;
				while (intersections[current_count])
					current_count++;

				// Create new array with space for both
				t_its **new_intersections = ft_calloc(current_count + 2, sizeof(t_its *));
				int j = 0;
				while (j < current_count)
				{
					new_intersections[j] = intersections[j];
					j++;
				}
				new_intersections[j] = obj_intersection;
				new_intersections[j + 1] = NULL;

				free(intersections);
				intersections = new_intersections;
			}
			total_intersections += obj_intersection->cnt;
		}
		else if (obj_intersection)
		{
			free_its(obj_intersection);
		}
	}

	// Sort intersections by t values
	if (total_intersections > 1)
	{
		// Count intersections for merge function
		int count = 0;
		while (intersections[count])
			count++;
		intersections = merge(intersections, count);
	}

	return(intersections);
}

void test_intersect_world(void)
{
	t_world *world = def_world();
	t_ray *rays = ray(tuple(4, 0.0, 0.0, -5.0, 1.0), tuple(4, 0.0, 0.0, 1.0, 0.0));
	t_its **intersections = intsect_world(world, rays);

	// Print intersections
	if (intersections)
	{
		for (int i = 0; intersections[i]; i++)
		{
			printf("Intersection %d: obj=%c, t values: ", i, intersections[i]->obj->type);
			for (int j = 0; j < intersections[i]->cnt; j++)
			{
				printf("%f ", intersections[i]->len[j]);
			}
			printf("\n");
		}
	}

	// free_its_s(intersections);
	// free_ray(rays);
	// free_world(world);
}
