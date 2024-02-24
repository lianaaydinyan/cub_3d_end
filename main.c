#include "../cub3d.h"

int	errorik(int flag)
{
	if (flag == M_ERROR)
		ft_putstr_fd("Error: map\n", 2);
	if (flag == F_ERROR)
		ft_putstr_fd("Error: wrong format of map\n", 2);
	else if (flag == T_ERROR)
		ft_putstr_fd("Error: some trouble with textures\n", 2);
	else if (flag == C_ERROR)
		ft_putstr_fd("Error: some trouble with colors\n", 2);
	else if (flag == E_ERROR)
		ft_putstr_fd("Error: something is missing\n", 2);
	else
		ft_putstr_fd("Error\n", 2);
	return (1);
}

void	hero_data_filling(t_data *data)
{
	
	chose_gamer_path(data);
	chose_gamer_path2(data);
	// data->pos_x = data->hero->x + 0.5;
	// data->pos_y = data->hero->y + 0.5;
	data->move_speed = 0.1;
	data->rot_speed = 0.3;
}

void	ft_filling(t_data *data)
{
	data->count = 0;
	data->nb = 0;
	data->to_map = 0;
	data->hit = 0;
	data->pitch = 100;
	data->side = 0;
	data->draw_end = 0;
	data->draw_start = 0;
	data->perp_wall_dist = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	hero_data_filling(data);
	texture_data_filling(data);
}



int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->textures = malloc(sizeof(char *) * 4);
	data->hero = malloc(sizeof(t_hero));
	data->mlx = malloc(sizeof(t_mlx));
	data->textures[0] = NULL;
	data->textures[1] = NULL;
	data->textures[2] = NULL;
	data->textures[3] = NULL;
	data->to_map = 0;
	data->map_h = 0;
	if (argc == 2)
	{
		if (parcing(data, argv))
			return (1);
		if (init_win(data))
			return (1);
		ft_filling(data);
		mlx_loop_hook(data->mlx->ptr, &just_do_it, data);
		mlx_hook(data->mlx->win, 3 , 1L << 3 , ft_movement, data); 
		mlx_hook(data->mlx->win, 2, 1L << 3 , key_hook, data);
		mlx_hook(data->mlx->win, 17, (1L << 17), key_cross, NULL);
		mlx_loop(data->mlx->ptr);
	}
	else
		return (errorik(42));
	return (0);
}