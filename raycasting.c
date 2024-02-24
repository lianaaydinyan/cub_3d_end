#include "../cub3d.h"

float	ft_abs(float num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	ft_raycasting(t_data *data)
{ 
	int i;
	i = -1;
	while (++i < screenWidth)
	{
		counting_delta_dist(data, i);
		calculate_step_init_side_dist(data);
		ft_dda_algorithm(data);
		camera_frame_counting(data);
		ft_texture_calculation(data);
		textures_drawing(data, i);
	}
	return (0);
}


void	counting_delta_dist(t_data *data, int i)
{
	data->camera_x = 2 * i / (double)screenWidth -  1;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	data->map_x = (int)data->hero->x;
	data->map_y = (int)data->hero->y;
	if ((data->ray_dir_x) == 0)
		data->delta_dist_x = 1e30;
	else
		data->delta_dist_x = ft_abs(1 / data->ray_dir_x);
	if ((data->ray_dir_y) == 0)
		data->delta_dist_y = 1e30;
	else
		data->delta_dist_y = ft_abs(1 / data->ray_dir_y);

}

void	calculate_step_init_side_dist(t_data *data)
{
		if (data->ray_dir_x < 0)
		{
			data->step_x = -1;
			data->side_dist_x = (data->pos_x - data->map_x) * data->delta_dist_x;
		}
		else
		{
			data->step_x = 1;
			data->side_dist_x = (data->map_x + 1.0 - data->pos_x) * data->delta_dist_x;
		}
		if (data->ray_dir_y < 0)
		{
			data->step_y = -1;
			data->side_dist_y = (data->pos_y - data->map_y) * data->delta_dist_y;
		}
		else
		{
			data->step_y = 1;
			data->side_dist_y = (data->map_y + 1.0 - data->pos_y) * data->delta_dist_y;
		}
}

void	ft_dda_algorithm(t_data *data)
{
	data->hit = 0;
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (data->map_c[data->map_x][data->map_y] == '1')
		{
			data->hit = 1;
		}
	}
} 

void	camera_frame_counting(t_data *data)
{
	
	if(data->side == 0)
	{

		data->perp_wall_dist = (data->side_dist_x - data->delta_dist_x);
		printf("\n\ndata->perp_wall_dist -> %f",data->perp_wall_dist);
	}
	else
	{
		data->perp_wall_dist = (data->side_dist_y - data->delta_dist_y);
		printf("\n\ndata->perp_wall_dist -> %f",data->perp_wall_dist);
	}
	data->line_height = (int)(screenHeight/ data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + screenHeight / 2 ;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = screenHeight / 2 + data->line_height / 2;
	if (data->draw_end >= screenHeight)
		data->draw_end = screenHeight;
}