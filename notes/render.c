/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:40 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:41 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*color_at(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	*hit_its;
	t_comps	*comps;
	t_tuple	*color;

	intersections = its_world(world, ray);
	if (!intersections)
		return (mult(world->a_color, world->a_ratio));
	hit_its = hit(intersections);
	if (!hit_its)
	{
		free_its_s(intersections);
		return (tuple(3, 0.0, 0.0, 0.0));
	}
	comps = prepare_computations(hit_its, ray);
	color = shade_hit(world, comps);
	free_its_s(intersections);
	free_comps(comps);
	return (color);
}

#define XOFFSET 0
#define YOFFSET 1
#define WORLD_X 2
#define WORLD_Y 3

t_ray	*ray_for_pixel(t_camera *cam, int px, int py)
{
	t_tuple	**inverse_transform;
	t_tuple	**origin;
	t_tuple	**pixel;
	t_tuple	*direction;
	double	c[4];

	c[XOFFSET] = (px + 0.5) * cam->pixel_size;
	c[YOFFSET] = (py + 0.5) * cam->pixel_size;
	c[WORLD_X] = cam->half_width - c[XOFFSET];
	c[WORLD_Y] = cam->half_height - c[YOFFSET];
	inverse_transform = cam->inverse_transform;
	pixel = matrix(2, tuple(4, c[WORLD_X], c[WORLD_Y], -1.0, 1.0));
	pixel = mxm(inverse_transform, transpose(pixel));
	pixel = transpose(pixel);
	origin = matrix(2, tuple(4, 0.0, 0.0, 0.0, 1.0));
	origin = mxm(inverse_transform, transpose(origin));
	origin = transpose(origin);
	direction = norm(sub(pixel[0], origin[0]));
	return (ray(origin[0], direction));
}

// Converts RGB values (0.0 to 1.0) to a hexadecimal color representation.
int	rgb_hex(double red, double green, double blue)
{
	int	hex;

	hex = 0;
	hex += (red * 255);
	hex = (hex << 8) + (green * 255);
	hex = (hex << 8) + (blue * 255);
	return (hex);
}

// Renders a pixel at the specified (x, y) position with the given color.
void	render_p(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->len) + (x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	render(t_img *canvas, t_camera *cam, t_world *world)
{
	t_ray	*ray;
	t_tuple	*color;
	int		y;
	int		x;

	y = -1;
	while (++y < (cam->vsize - 1))
	{
		x = -1;
		while (++x < (cam->hsize - 1))
		{
			ray = ray_for_pixel(cam, x, y);
			color = color_at(world, ray);
			render_p(canvas, x, y, rgb_hex(color->val[0],
					color->val[1], color->val[2]));
			free_ray(ray);
		}
	}
	printf("Rendered\n");
}
