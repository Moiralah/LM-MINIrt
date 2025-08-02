/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:38:47 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 22:55:53 by huidris          ###   ########.fr       */
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

#define FORWARD 0
#define UPNORM 1
#define LEFT 2
#define TRUEUP 3

t_tuple	**view_transform(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple	*v[4];
	t_tuple	**view_matrix;
	t_tuple	**orientation;
	t_tuple	**translation_matrix;

	v[FORWARD] = norm(sub(to, from));
	v[UPNORM] = norm(up);
	v[LEFT] = cross(v[FORWARD], v[UPNORM]);
	v[TRUEUP] = cross(v[LEFT], v[FORWARD]);
	orientation = matrix(5, v[LEFT], v[TRUEUP], mult(v[FORWARD], -1.0), NULL);
	orientation[3] = tuple(4, 0.0, 0.0, 0.0, 1.0);
	translation_matrix = translate(4, -from->val[0], -from->val[1], -from->val[2]);
	view_matrix = mxm(orientation, translation_matrix);
	return (view_matrix);
}
