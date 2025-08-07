/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:55 by huidris           #+#    #+#             */
/*   Updated: 2025/08/07 23:12:08 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exiting(t_mlx_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

void	rerender(t_mlx_data *data)
{
	t_world	*w;
	t_data	*world_data;

	world_data = input_data(data->fname);
	free_world(data->w);
	w = world(world_data);
	data->w = w;
	render(&(data->img), w->c, w);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	key__hook(int keycode, t_mlx_data *data)
{
	if ((keycode == XK_R) || (keycode == XK_r))
		rerender(data);
	if (keycode == 65307 || keycode == 53)
		exiting(data);
	return (0);
}

void	start_window(t_mlx_data *data, t_world *w, t_img img)
{
	if (w->c)
	{
		render(&img, w->c, w);
		mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
		mlx_key_hook(data->win, key__hook, data);
		mlx_hook(data->win, 17, 1L << 0, exiting, data);
		mlx_loop(data->mlx);
	}
}

int	main(int ac, char **av)
{
	t_world		*w;
	t_data		*world_data;
	t_mlx_data	data;
	t_img		img;

	if (ac != 2)
		return (perr("Error: Invalid input. < ./miniRT xxx.rt >"), -1);
	world_data = input_data(av[1]);
	w = world(world_data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Render");
	img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	data.fname = av[1];
	data.w = w;
	data.img = img;
	start_window(&data, w, img);
	mlx_destroy_image(data.mlx, img.img);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (free(data.mlx), free_world(data.w), 0);
}
