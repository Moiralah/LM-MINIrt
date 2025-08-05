/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:55 by huidris           #+#    #+#             */
/*   Updated: 2025/08/05 17:02:18 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exiting(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
	return (0);
}

int	key__hook(int keycode, t_mlx_data *data)
{
	if (keycode == 65307 || keycode == 53)
		exiting(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*world_data;
	t_world		*w;
	t_mlx_data	data;
	t_img		img;

	if (ac != 2)
		return (perr("Invalid input. < ./miniRT xxx.rt >"), -1);
	world_data = input_data(av[1]);
	if (!world_data->pl)
		printf("NULL\n");
	w = world(world_data);
	if (!world_data->pl)
		printf("NULL\n");
	free_data(world_data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Render");
	img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	render(&img, w->c, w);
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	mlx_key_hook(data.win, key__hook, &data);
	mlx_hook(data.win, 17, 1L << 0, exiting, &data);
	mlx_loop(data.mlx);
	free_world(w);
	return (0);
}

/* int	main(void)
{
	t_its	**l1;
	t_its	**l2;
	double	f;

	l1 = its_s(3, its(NULL, 'S'), its(NULL, 'S'), its(NULL, 'S'));
	l2 = its_s(3, its(NULL, 'S'), its(NULL, 'S'), its(NULL, 'S'));
	l2 = merge_its_s(l1, l2);
	l2 = merge(l2, 6);
	free_its_s(l2);
	f = ft_atof("7.11");
	printf("%f\n", f);
	free2d(ft_split("a b c d  f pl kw 203qh \n dj l", ' '));
} */
