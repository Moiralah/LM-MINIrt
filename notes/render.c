/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:40 by huidris           #+#    #+#             */
/*   Updated: 2025/08/05 17:51:11 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
t_ray	*create_ray(t_tuple **inv_m, double world_x, double world_y)
{
	t_tuple	*world[2];
	t_tuple	*dir[2];
	t_tuple	*obj_p[2];

	world[0] = tuple(4, world_x, world_y, -1.0, 1.0);
	if (!world[0])
		return (NULL);
	obj_p[0] = world_to_obj_point(inv_m, world[0]);
	free_t(world[0]);
	if (!obj_p[0])
		return (NULL);
	world[1] = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!world[1])
		return (free_t(obj_p[0]), NULL);
	obj_p[1] = world_to_obj_point(inv_m, world[1]);
	free_t(world[1]);
	if (!obj_p[1])
		return (free_t(obj_p[0]), free_t(world[1]), NULL);
	dir[0] = sub(obj_p[0], obj_p[1]);
	free_t(obj_p[0]);
	if (!dir[0])
		return (NULL);
	dir[1] = norm(dir[0]);
	if (!dir[1])
		return (free_t(dir[0]), free_t(world[1]), NULL);
	return (ray(obj_p[1], dir[1]));
}*/

#define XOFFSET 0
#define YOFFSET 1
#define WORLD_X 2
#define WORLD_Y 3

t_ray	*ray_for_pixel(t_camera *cam, int px, int py)
{
	t_tuple	**inverse_transform;
	double	c[4];

	c[XOFFSET] = (px + 0.5) * cam->pixel_size;
	c[YOFFSET] = (py + 0.5) * cam->pixel_size;
	c[WORLD_X] = cam->half_width - c[XOFFSET];
	c[WORLD_Y] = cam->half_height - c[YOFFSET];
	inverse_transform = cam->inverse_transform;
	return (create_ray(inverse_transform, c[WORLD_X], c[WORLD_Y]));
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

	printf("Start rendering\n");
	y = -1;
	while (++y < (cam->vsize))
	{
		x = -1;
		while (++x < (cam->hsize))
		{
			//printf("X: %d | Y: %d\n", x, y);
			ray = ray_for_pixel(cam, x, y);
			color = color_at(world, ray);
			clamp(color, 0.0, 1.0);
			render_p(canvas, x, y, rgb_hex(color->val[0],
					color->val[1], color->val[2]));
			free_t(color);
			free_ray(ray);
		}
	}
	printf("Rendered\n");
}
