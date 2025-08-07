/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:09:41 by huidris           #+#    #+#             */
/*   Updated: 2025/08/06 01:17:23 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define SP	0.9
#define DF	0.9
#define SH	200.0

int	add_sphere(t_world *w, t_data *data, t_sp *sp_link, int i)
{
	t_mat	*m;
	t_tuple	*mat_val;

	while (sp_link)
	{
		mat_val = tuple(4, data->a_ratio, SP, DF, SH);
		m = material(sp_link->color, mat_val);
		free_t(mat_val);
		w->obj[++i] = sphere(sp_link->ori, m, sp_link->rad);
		sp_link = sp_link->next;
	}
	return (i);
}

int	add_plane(t_world *w, t_data *data, t_pl *pl_link, int i)
{
	t_mat	*m;
	t_tuple	*mat_val;

	while (pl_link)
	{
		mat_val = tuple(4, data->a_ratio, SP, DF, SH);
		m = material(pl_link->color, mat_val);
		free_t(mat_val);
		w->obj[++i] = plane(pl_link->ori, pl_link->normalv, m);
		pl_link = pl_link->next;
	}
	return (i);
}

int	add_cylinder(t_world *w, t_data *data, t_cy *cy_link, int i)
{
	t_mat	*m;
	t_tuple	*mat_val;
	t_tuple	**cy_val;
	t_tuple	*cy_dim;

	while (cy_link)
	{
		mat_val = tuple(4, data->a_ratio, SP, DF, SH);
		m = material(cy_link->color, mat_val);
		free_t(mat_val);
		cy_val = matrix(2, cy_link->ori, cy_link->n);
		cy_dim = tuple(4, cy_link->rad, cy_link->h, 1.0, -1.0);
		w->obj[++i] = cylinder(cy_val, m, cy_dim, 1);
		free_m(cy_val, len_m(cy_val));
		free_t(cy_dim);
		cy_link = cy_link->next;
	}
	return (i);
}

void	set_obj(t_world *w, t_data *data)
{
	t_sp		*sp_link;
	t_pl		*pl_link;
	t_cy		*cy_link;
	int			i;

	i = -1;
	sp_link = data->sp;
	i = add_sphere(w, data, sp_link, i);
	pl_link = data->pl;
	i = add_plane(w, data, pl_link, i);
	cy_link = data->cy;
	i = add_cylinder(w, data, cy_link, i);
}
