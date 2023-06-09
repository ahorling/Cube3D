/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:33:10 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/25 19:59:36 by fholwerd      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42.h"
#include "raycaster.h"
#include "set_background.h"
#include "stop.h"

static void	move_player(t_raycaster *rc, double move_x, double move_y)
{
	if (rc->map[(int)rc->py][(int)(rc->px + move_x)] == 0)
		rc->px += move_x;
	if (rc->map[(int)(rc->py + move_y)][(int)rc->px] == 0)
		rc->py += move_y;
}

static void	change_pitch(t_raycaster *rc, int change)
{
	if (rc->pitch + change > -1 * (rc->screen_height / 2)
		&& rc->pitch + change < rc->screen_height / 2)
	{
		rc->pitch += change;
		set_background(*rc);
	}
}

void	rotate_player(t_raycaster *rc, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = rc->pdx;
	rc->pdx = rc->pdx * cos(rot) - rc->pdy * sin(rot);
	rc->pdy = old_dir_x * sin(rot) + rc->pdy * cos(rot);
	old_plane_x = rc->cpx;
	rc->cpx = rc->cpx * cos(rot) - rc->cpy * sin(rot);
	rc->cpy = old_plane_x * sin(rot) + rc->cpy * cos(rot);
}

void	movement(t_raycaster *rc)
{
	mlx_t		*mlx;
	double		move_x;
	double		move_y;

	mlx = rc->mlx;
	move_x = rc->mspeed * rc->pdx;
	move_y = rc->mspeed * rc->pdy;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		move_player(rc, move_x, move_y);
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move_player(rc, -move_x, -move_y);
	if (mlx_is_key_down(mlx, MLX_KEY_Q) || mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player(rc, -rc->rspeed);
	if (mlx_is_key_down(mlx, MLX_KEY_E) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player(rc, rc->rspeed);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(rc, move_y, -move_x);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(rc, -move_y, move_x);
	if (mlx_is_key_down(mlx, MLX_KEY_KP_ADD))
		change_pitch(rc, 10);
	if (mlx_is_key_down(mlx, MLX_KEY_KP_SUBTRACT))
		change_pitch(rc, -10);
}
