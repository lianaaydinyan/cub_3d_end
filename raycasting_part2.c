#include "../cub3d.h"

void	ft_texture_calculation(t_data	*data)
{
	double wall_x;

	wall_x = 0.0;
	if (data->side == 0)
		wall_x = data->pos_y + data->perp_wall_dist * data->ray_dir_y;
	else
		wall_x = data->pos_x + data->perp_wall_dist * data->ray_dir_x;
	wall_x -= floor(wall_x);
	data->tex_x = (int)(wall_x * (double)64);
	if (data->side == 0 && data->ray_dir_x > 0)
		data->tex_x = 64 - data->tex_x - 1;
	if (data->side == 1 && data->ray_dir_y < 0)
		data->tex_x = 64 - data->tex_x - 1;	
} 


int choose_rigth_texture(t_data *data)
{
	if (data->side && data->ray_dir_y > 0)
		return(0);
	else if (data->side && data->ray_dir_y < 0)
		return (1);
	else if (!data->side && data->ray_dir_x > 0)
			return(2);
	else if (!data->side && data->ray_dir_x < 0)
		return (3);
	return (-1);
}

void	textures_drawing(t_data *data, int i)
{
	int 	x;
	char 	*dst_tex;
	double 	tex_pos;
	double 	step;
	int		tex_y;

	step = 1.0 * 64 / data->line_height;
	int 	start = data->draw_start;
	x = choose_rigth_texture(data);
	tex_pos = (data->draw_start  - screenHeight / 2 + data->line_height / 2) * step ;
	while (start < data->draw_end)
	{
		tex_y = (int)tex_pos & (64 - 5);
		tex_pos += step;
		dst_tex = data->texturess[x].addr + (tex_y) * \
				data->texturess[x].line_length + data->tex_x * (data->texturess[x].bits_per_pixel / 8);
		my_mlx_pixel_put(data, i, start++,*(unsigned int *)dst_tex);
	}

}

void	texture_data_filling(t_data *data)
{

	int size = 64;
	data->texturess[0].img = mlx_xpm_file_to_image(data->mlx->ptr, "textures/path_to_the_south_texture.xpm", &size, &size);
	data->texturess[1].img = mlx_xpm_file_to_image(data->mlx->ptr, "textures/path_to_the_north_texture.xpm" , &size, &size);
	data->texturess[2].img = mlx_xpm_file_to_image(data->mlx->ptr, "textures/path_to_the_west_texture.xpm", &size, &size);
	data->texturess[3].img = mlx_xpm_file_to_image(data->mlx->ptr, "textures/path_to_the_east_texture.xpm", &size, &size);
	int i = 0;
	while (i < 4)
	{

		data->texturess[i].addr = mlx_get_data_addr(data->texturess[i].img, &data->texturess[i].bits_per_pixel, &data->texturess[i].line_length,&data->texturess[i].endian);
		i++;
	}
}

void	chose_gamer_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_h)
	{
		j = 0;
		//petqa loop-i mej data->size i poxaren amenaerkar toxy-i leny yntrenq
		while (j < data->map_h)
		{
			if (ft_strrchr(("NWSE"),data->map[i][j]))
				{
					data->hero->x = i;
					data->pos_x = i;
					data->pos_y = j;
					data->hero->y = j;
					data->hero->view = data->map[i][j];
					data->map[i][j] = 0;
					return;
				}
			j++;
		}
		i++;
	}
}
