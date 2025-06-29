#include "minirt.h"

void	cast_rays(t_img img, t_sphere *sphere, t_tuple *ori, int hit, int nohit, int w, int h)
{
	t_its	*its;
	t_ray	*r;
	t_tuple	*dir;
	//t_tuple	*hit_loc;
	double	*cords;
	int		i[2];

	i[0] = w - 1;
	i[1] = h - 1;
	while (i[0] >= 0)
	{
		dir = tuple(4.0, ((float) i[0]), ((float) i[1]), 0.0, 1.0);
		cords = dir->val;
		dir->val = sub(cords, ori->val, ori->size);
		free(cords);
		r = ray(ori, dir);
		its = sphere_its(r, sphere);
		if (!its)
			return ;
		if (!its->len)
			render_p(&img, i[0], i[1], nohit);
		else
		{
			//hit_loc = travel(r, its->len[1]);
			//printf("Hit at %f | %f with t: %f\n", hit_loc->val[1], hit_loc->val[2], its->len[1]);
			render_p(&img, i[0], i[1], hit);
		}
		printf("%d | %d\n", i[0], i[1]);
		i[1]--;
		if ((i[1] < 0) && (i[0]--))
			i[1] = h;
		//break;
		/* if (!its->len)
			free_t(hit_loc);
		free_t(dir);
		free(r);
		free(its); */
	}
}

int	main(void)
{
	t_img		img;
	t_sphere	*s;
	t_tuple		*ori;
	void		*mlx;
	void		*win;
	int			black;
	int			yellow;
	int			w;
	int			h;

	w = 100;
	h = 100;
	ori = tuple(4.0, w / 2.0, h / 2.0, -5.0, 1.0);
	black = rgb_hex(0.0, 0.0, 0.0);
	yellow = rgb_hex(1.0, 1.0, 0.0);
	s = sphere(ori, 1.0);
	mlx = mlx_init();
	win = mlx_new_window(mlx, w, h, "Sphere");
	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	cast_rays(img, s, ori, yellow, black, w, h);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
