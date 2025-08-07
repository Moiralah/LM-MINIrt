/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 00:52:36 by huidris           #+#    #+#             */
/*   Updated: 2025/08/04 00:52:39 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_cylinder(t_cylinder *cy)
{
	free_m(cy->inv_tf, len_m(cy->inv_tf));
	free_t(cy->ori);
	free_mat(cy->mat);
	free(cy);
}

void	free_sphere(t_sphere *sp)
{
	free_m(sp->inv_tf, len_m(sp->inv_tf));
	free_t(sp->ori);
	free_mat(sp->mat);
	free(sp);
}

void	free_plane(t_plane *pl)
{
	free_m(pl->inv_tf, len_m(pl->inv_tf));
	free_t(pl->ori);
	free_mat(pl->mat);
	free(pl);
}
