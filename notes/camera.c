#include "minirt.h"

t_camera	*camera(double hsize, double vsize, double field_of_view)
{
	t_camera	*cam;
	double		half_view;
	double		aspect;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->field_of_view = field_of_view;
	cam->transform = identity(4);
	half_view = tan(field_of_view / 2);
	aspect = (double)hsize / (double)vsize;
	if (aspect >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / hsize;
	return (cam);
}

#define XOFFSET 0
#define YOFFSET 1
#define WORLD_X 2
#define WORLD_Y 3

t_ray	*ray_for_pixel(t_camera *cam, int px, int py)
{
	double	c[4];
	t_tuple	*pixel;
	t_tuple	*origin;
	t_tuple	*direction;
	t_tuple	**inverse_transform;

	c[XOFFSET] = (px + 0.5) * cam->pixel_size;
	c[YOFFSET]= (py + 0.5) * cam->pixel_size;
	c[WORLD_X] = cam->half_width - c[XOFFSET];
	c[WORLD_Y] = cam->half_height - c[YOFFSET];
	inverse_transform = inverse(cam->transform);
	pixel = tuple(4.0, c[WORLD_X], c[WORLD_Y], -1.0, 1.0);
	pixel = mxm(inverse_transform, &pixel);
	origin = tuple(4.0, 0.0, 0.0, 0.0, 1.0);
	origin = mxm(inverse_transform, &origin);
	direction = norm(sub(pixel, origin));
	return (ray(origin, norm(direction)));
}

t_img *render(t_camera *cam, t_world *world)
{
	t_img	*canvas;
	t_ray	*ray;
	int		color;
	int		x;
	int		y;

	canvas = malloc(sizeof(t_img));
	if (!canvas)
		return (NULL);
	canvas->w = cam->hsize;
	canvas->h = cam->vsize;
	y = 0;
	while (y < cam->vsize - 1)
	{
		x = 0;
		while (x < cam->hsize - 1)
		{
			ray = ray_for_pixel(cam, x, y);
			color = color_at(world, ray);
			render_p(canvas, x, y, color);
			free_ray(ray);
			x++;
		}
		y++;
	}
	return (canvas);
}
