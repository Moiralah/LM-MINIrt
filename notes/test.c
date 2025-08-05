/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:55 by huidris           #+#    #+#             */
/*   Updated: 2025/08/05 15:58:29 by huidris          ###   ########.fr       */
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
	t_world		*w;
	t_mlx_data	data;
	t_img		img;

	if (ac != 2)
		return (perr("Invalid input. < ./miniRT xxx.rt >"), -1);
	w = world(input_data(av[1]));
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
	free(w->c->inverse_transform);
	free(w->c);
	return (0);
 }
