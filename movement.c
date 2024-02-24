#include "../cub3d.h"

int	ft_movement(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 126) // its for  W and up	
		qayl_araj(data);
	else if (keycode == 0 || keycode == 123) // its for A and left
		depi_dzax(data);
	else if (keycode == 1 || keycode == 125) // its for S and down
		qayl_het(data);
	else if (keycode == 2 || keycode == 124) // its for D and rigth
		depi_aj(data);
	return 0;
}
void	qayl_araj(t_data *data)
{
	printf("\n\naraj gna miqich\n\n");
	if (!(data->map[(int)(data->pos_x + data->dir_x * data->move_speed)][(int)data->pos_y]))
		data->pos_x += data->dir_x * data->move_speed;
	if (!(data->map[(int)data->pos_x][(int)(data->pos_y + data->dir_y * data->move_speed)]))
		data->pos_y += data->dir_y * data->move_speed;
}

void	qayl_het(t_data *data)
{
	printf("\n\nhet gna miqich\n\n");
	if (!(data->map[(int)(data->pos_x - data->dir_x * data->move_speed)][(int)data->pos_y]))
		data->pos_x -= data->dir_x * data->move_speed;
	if (!(data->map[(int)data->pos_x][(int)(data->pos_y - data->dir_y * data->move_speed)]))
		data->pos_y -= data->dir_y * data->move_speed;
}

void	depi_aj(t_data *data)
{
	printf("\n\najjjjjj miqich\n\n");
	double old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-data->rot_speed) - data->dir_y * sin(-data->rot_speed);
	data->dir_y = old_dir_x * sin(-data->rot_speed) + data->dir_y * cos(-data->rot_speed);
	double old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-data->rot_speed) - data->plane_y * sin(-data->rot_speed);
	data->plane_y = old_plane_x * sin(-data->rot_speed) + data->plane_y * cos(-data->rot_speed);
}

void	depi_dzax(t_data *data)
{
	printf("\n\ndzaaxxxxx miqich\n\n");
	double old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(data->rot_speed) - data->dir_y * sin(data->rot_speed);
	data->dir_y = old_dir_x * sin(data->rot_speed) + data->dir_y * cos(data->rot_speed);
	double	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(data->rot_speed) - data->plane_y * sin(data->rot_speed);
	data->plane_y = old_plane_x * sin(data->rot_speed) + data->plane_y * cos(data->rot_speed);
}
