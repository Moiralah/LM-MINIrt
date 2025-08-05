/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 00:53:03 by huidris           #+#    #+#             */
/*   Updated: 2025/08/05 22:58:07 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_sp_link(t_sp *sp_link)
{
	t_sp	*temp;

	while (sp_link)
	{
		free_t(sp_link->ori);
		temp = sp_link;
		sp_link = sp_link->next;
		free(temp);
	}
}

void	free_pl_link(t_pl *pl_link)
{
	t_pl	*temp;

	while (pl_link)
	{
		free_t(pl_link->ori);
		free_t(pl_link->normalv);
		temp = pl_link;
		pl_link = pl_link->next;
		free(temp);
	}
}

void	free_cy_link(t_cy *cy_link)
{
	t_cy	*temp;

	while (cy_link)
	{
		temp = cy_link;
		cy_link = cy_link->next;
		free(temp);
	}
}

void	free_data(t_data *data)
{
	free_sp_link(data->sp);
	free_pl_link(data->pl);
	free_cy_link(data->cy);
	free2d(data->data);
	free_t(data->l_color);
	free_t(data->a_color);
	free_t(data->c_dir);
	free(data);
}
