/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:38:47 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 18:12:04 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*camera(int hsize, int vsize, double field_of_view)
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
	cam->inverse_transform = inverse(cam->transform);
	half_view = tan(field_of_view / 2);
	aspect = (double) hsize / (double) vsize;
	cam->half_width = half_view;
	cam->half_height = half_view / aspect;
	if (aspect < 1)
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
	t_tuple	**inverse_transform;
	t_tuple	**origin;
	t_tuple	**pixel;
	t_tuple	*direction;
	double	c[4];

	c[XOFFSET] = (px + 0.5) * cam->pixel_size;
	c[YOFFSET]= (py + 0.5) * cam->pixel_size;
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
			render_p(canvas, x, y, rgb_hex(color->val[0], color->val[1], color->val[2]));
			free_ray(ray);
		}
	}
}
