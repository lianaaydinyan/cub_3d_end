/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:08:06 by marihovh          #+#    #+#             */
/*   Updated: 2024/02/21 16:02:28 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int init_win(t_data *data)
{
    data->win_w = screenWidth;
    data->win_h = screenHeight;
	data->mlx->ptr = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->ptr, data->win_w,
       data->win_h, "Cub3d");
    return (0);
}

void draw_colors(t_data *data)
{
    int x = 0, y = 0;
    while (y < data->win_h / 2)
	{
        x = 0;
        while (x < data->win_w)
		{
            my_mlx_pixel_put(data, x, y, data->celling_c);
            x++;
        }
        y++;
    }
    y = data->win_h / 2;
    while (y < data->win_h)
	{
        x = 0;
        while (x < data->win_w)
		{
            my_mlx_pixel_put(data, x, y, data->flooring_c);
            x++;
        }
        y++;
    }
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// if (x > 0 && y > 0 && data->win_w > x && data->win_h > y)
	// {
		dst = data->mlx->image.addr + (y * data->mlx->image.line_length + \
				x * (data->mlx->image.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	// }
}

int just_do_it(t_data *data)
{
	data->mlx->image.img = mlx_new_image(data->mlx->ptr, screenWidth, screenHeight);
	data->mlx->image.addr = mlx_get_data_addr(data->mlx->image.img , \
	&data->mlx->image.bits_per_pixel, &data->mlx->image.line_length, &data->mlx->image.endian);
	data->celling_c = 0x87CEEB;
    data->flooring_c = 0x0b701a;
    draw_colors(data); 
	ft_raycasting(data);
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->image.img, 0, 0);
	mlx_destroy_image(data->mlx->ptr , data->mlx->image.img);
	return (0);
}