#include "minirt.h"

void	cast_rays(t_img img, t_sphere *sphere, t_light *light, t_tuple *ori, int nohit)
{
	t_its	*its;
	t_ray	*r;
	t_tuple	*dir;
	t_tuple	*temp;
	t_tuple	*e;
	t_tuple	*n;
	t_tuple	*hit;
	t_tuple	*ray_origin;
	double	scaled_w;
	double	scaled_h;
	double	wall_size;
	double	wall_p[2];
	int		i[2];
	int		hit_colour;

	i[0] = img.w - 1;
	i[1] = img.h - 1;
	wall_size = 7.0;
	scaled_w = wall_size / img.w;
	scaled_h = wall_size / img.h;
	while (i[0] >= 0)
	{
		// Calculate wall point in world coordinates
		wall_p[0] = (wall_size / 2) - (scaled_w * i[0]);
		wall_p[1] = (wall_size / 2) - (scaled_h * i[1]);

		// Create direction vector from camera to wall point
		dir = tuple(4.0, wall_p[0], wall_p[1], 0.0, 1.0);
		temp = dir;
		dir = sub(dir, ori);
		free_t(temp);
		temp = dir;
		dir = norm(dir);
		free_t(temp);

		// Create a copy of the origin for the ray
		ray_origin = tuple(4.0, ori->val[0], ori->val[1], ori->val[2], ori->val[3]);

		// Create ray from camera position
		r = ray(ray_origin, dir);
		e = mult(r->dir, -1);
		its = sphere_its(r, sphere);
		if (!its)
			return (free_ray(r));
		if ((!its->len) || (its->len[0] < 0))
			render_p(&img, i[0], i[1], nohit);
		else
		{
			hit = travel(r, its->len[0]);
			n = normal_at_obj(get_obj_tf(its->obj), hit, tuple(4.0, 0.0, 0.0, 0.0, 1.0));
			hit_colour = lighting(get_obj_mat(its->obj), light, matrix(4.0, hit, e, n));
			render_p(&img, i[0], i[1], hit_colour);
		}
		i[1]--;
		if ((i[1] < 0) && (i[0]--))
			i[1] = img.h - 1;
		free_ray(r);
		free_its(its);
	}
}

int	main(void)
{

	// t_img		img;
	// t_mat		*mat;
	// t_sphere	*s;
	// t_light		*l;
	// t_tuple		*ori;
	// void		*mlx;
	// void		*win;
	// int			black;
	// int			blue;
	// int			light_colour;

	// img.w = 100;
	// img.h = 100;
	// ori = tuple(4.0, 0.0, 0.0, -5.0, 1.0);
	// black = rgb_hex(0.0, 0.0, 0.0);
	// blue = rgb_hex(1.0, 0.2, 1.0);
	// light_colour = rgb_hex(1.0, 1.0, 1.0);
	// l = light(tuple(4, -10.0, 10.0, -10.0, 1.0), light_colour);
	// mat = material(blue, tuple(4, 1.0, 1.0, 1.0, 1.0));
	// s = sphere(tuple(4.0, 0.0, 0.0, 10, 1.0), mat, 1.0);
	// mlx = mlx_init();
	// win = mlx_new_window(mlx, img.w, img.h, "Sphere");
	// img.img = mlx_new_image(mlx, img.w, img.h);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	// cast_rays(img, s, l, ori, black);
	// mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	// mlx_loop(mlx);
	// mlx_destroy_display(mlx);
	// free(mlx);

	test_intersect_world();
	return (0);
}
