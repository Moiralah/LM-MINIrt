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

void	initialise_cam(t_camera *cam)
{
	double		half_view;
	double		aspect;

	aspect = (double) cam->hsize / (double) cam->vsize;
	half_view = tan(cam->fov / 2);
	cam->half_width = half_view;
	cam->half_height = half_view / aspect;
	if (aspect < 1)
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / cam->hsize;
}

t_camera	*camera(t_tuple **tm, double fov, int hsize, int vsize)
{
	t_camera	*cam;
	t_tuple		**transform;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	transform = view_transform(tm[0], tm[1], tm[2]);
	if (!transform)
		return (free(cam), NULL);
	cam->inverse_transform = inverse(transform);
	free_m(transform, len_m(transform));
	if (!cam->inverse_transform)
		return (free(cam), NULL);
	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->fov = fov;
	initialise_cam(cam);
	return (cam);
}

t_tuple	**get_forward_up(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple	*cam_dir;
	t_tuple	*forward;
	t_tuple	*upnorm;

	cam_dir = sub(to, from);
	if (!cam_dir)
		return (NULL);
	forward = norm(cam_dir);
	free_t(cam_dir);
	if (!forward)
		return (NULL);
	upnorm = norm(up);
	if (!upnorm)
		return (free_t(forward), NULL);
	return (matrix(2, forward, upnorm));
}

t_tuple	**get_orientation(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple	**forward_up;
	t_tuple	*neg_forward;
	t_tuple	*trueup;
	t_tuple	*left;

	forward_up = get_forward_up(from, to, up);
	if (!forward_up)
		return (NULL);
	left = cross(forward_up[0], forward_up[1]);
	if (!left)
		return (free_m(forward_up, len_m(forward_up)), NULL);
	trueup = cross(left, forward_up[0]);
	if (!trueup)
		return (free_m(forward_up, len_m(forward_up)), free_t(left), NULL);
	neg_forward = mult(forward_up[0], -1.0);
	free_m(forward_up, len_m(forward_up));
	if (!neg_forward)
		return (free_t(left), free_t(trueup), NULL);
	return (matrix(4, left, trueup, neg_forward, NULL));
}

t_tuple	**view_transform(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple	**view_matrix;
	t_tuple	**orientation;
	t_tuple	**trans_m;

	orientation = get_orientation(from, to, up);
	if (!orientation)
		return (NULL);
	orientation[3] = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!orientation[3])
		return (free_m(orientation, 3), NULL);
	trans_m = translate(4, -from->val[0], -from->val[1], -from->val[2]);
	if (!trans_m)
		return (free_m(orientation, len_m(orientation)), NULL);
	view_matrix = mxm(orientation, trans_m);
	free_m(orientation, len_m(orientation));
	free_m(trans_m, len_m(trans_m));
	return (view_matrix);
}
