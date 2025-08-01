/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:39:57 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 22:54:03 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_its	**add_its(t_its **intersections, t_its *obj_its, int *total_its)
{
	t_its	**temp;
	int		i;

	temp = ft_calloc(*total_its + 2, sizeof(t_its *));
	i = -1;
	while (++i < *total_its)
		temp[i] = intersections[i];
	temp[*total_its] = obj_its;
	temp[*total_its + 1] = NULL;
	free(intersections);
	(*total_its)++;
	return (temp);
}

t_its	**its_world(t_world *world, t_ray *ray)
{
	t_its	**merged_list;
	t_its	**its_list;
	int		i;

	i = -1;
	merged_list = NULL;
	while (world->object[++i])
	{
		its_list = calculate_its(world->object[i], ray);
		if (!merged_list)
			merged_list = its_list;
		else if (its_list)
			merged_list = merge_its_s(merged_list, its_list);
	}
	if (!merged_list)
		return (NULL);
	i = 0;
	while (merged_list[i])
		i++;
	return (merge(merged_list, i));
}

t_world	*world(t_data *data)
{
	t_world		*w;
	t_mat		*m;
	double		sh;
	double		sp;
	double		df;
	int		i;

	sp = 0.9;
	df = 0.9;
	sh = 200.0;
	w = malloc(sizeof(t_world));
	if (!w)
		return (NULL);
	w->a_ratio = data->a_ratio;
	w->a_color = copy_t(data->a_color);
	w->light = light(data->l_pos, mult(data->l_color, data->l_ratio));
	w->object = malloc((data->obj_amt + 1) * sizeof(t_obj *));
	w->object[data->obj_amt] = NULL;
	i = -1;
	while (data->sp)
	{
		m = material(data->sp->color, tuple(4, data->a_ratio, sp, df, sh));
		w->object[++i] = sphere(data->sp->ori, m, data->sp->rad);
		data->sp = data->sp->next;
	}
	while (data->pl)
	{
		m = material(data->pl->color, tuple(4, data->a_ratio, sp, df, sh));
		w->object[++i] = plane(data->pl->ori, m);
		data->pl = data->pl->next;
	}
	while (data->cy)
	{
		m = material(data->cy->color, tuple(4, data->a_ratio, sp, df, sh));
		w->object[++i] = cylinder(data->cy->ori, data->cy->normalv, m, tuple(2, data->cy->rad, data->cy->height));
		data->cy = data->cy->next;
	}
	return (w);
}

/* t_its	**add_its(t_its **intersections, t_its *obj_its, int *total_its)
{
	t_its	**temp;
	int		i;

	temp = ft_calloc(*total_its + 2, sizeof(t_its *));
	i = -1;
	while (++i < *total_its)
		temp[i] = intersections[i];
	temp[*total_its] = obj_its;
	temp[*total_its + 1] = NULL;
	free(intersections);
	(*total_its)++;
	return (temp);
}

t_its	**its_world(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	*obj_its[2];
	int		total;
	int		i;
	int		j;

	intersections = ft_calloc(1, sizeof(t_its *));
	total = 0;
	i = -1;
	while (world->object[++i])
	{
		obj_its[0] = intersect(ray, world->object[i]);
		j = -1;
		while (++j < obj_its[0]->cnt)
		{
			obj_its[1] = its(obj_its[0]->obj, NULL, 1);
			obj_its[1]->len = malloc(sizeof(double));
			obj_its[1]->len[0] = obj_its[0]->len[j];
			intersections = add_its(intersections, obj_its[1], &total);
		}
	}
	intersections = merge(intersections, total);
	return (intersections);
} */

t_its	**merge_its_s(t_its **list1, t_its **list2)
{
	t_its	**merged;
	int	len1;
	int	len2;

	len1 = 0;
	len2 = 0;
	if (!list1 && !list2)
		return (NULL);
	if (!list1)
		return (list2);
	else if (!list2)
		return (list1);
	while (list1[len1])
		len1++;
	while (list2[len2])
		len2++;
	merged = calloc(len1 + len2 + 1, sizeof(t_its *));
	merged[len1 + len2] = NULL;
	while (--len2 >= 0)
		merged[len2 + len1] = list2[len2];
	while (--len1 >= 0)
		merged[len1] = list1[len1];
	free(list1);
	free(list2);
	return (merged);
}
