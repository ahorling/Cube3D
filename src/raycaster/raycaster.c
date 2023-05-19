/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fholwerd <fholwerd@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 13:31:41 by fholwerd      #+#    #+#                 */
/*   Updated: 2023/05/19 22:14:14 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "draw_walls.h"
#include "raycaster.h"
#include "stop.h"

// Length of ray from current position to next x or y-side
// Delta distance calculation
static void	delta_distance_calculation(t_raycaster *rc)
{
	if (rc->rdx == 0)
		rc->d_dist_x = 1e30;
	else
		rc->d_dist_x = fabs(1 / rc->rdx);
	if (rc->rdy == 0)
		rc->d_dist_y = 1e30;
	else
		rc->d_dist_y = fabs(1 / rc->rdy);
}

// Calculate step and initial side distance
static void	step_calculation(t_raycaster *rc)
{
	if (rc->rdx < 0)
	{
		rc->step_x = -1;
		rc->s_dist_x = (rc->px - rc->map_x) * rc->d_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->s_dist_x = (rc->map_x + 1.0 - rc->px) * rc->d_dist_x;
	}
	if (rc->rdy < 0)
	{
		rc->step_y = -1;
		rc->s_dist_y = (rc->py - rc->map_y) * rc->d_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->s_dist_y = (rc->map_y + 1.0 - rc->py) * rc->d_dist_y;
	}
}

// DDA or "Digital Differential Analysis". DDA is a fast algorithm typically
// used on square grids to find which squares a line hits (for example to
// draw a line on a screen, which is a grid of square pixels).
// rc->side is set to 0 for vertical hit or 1 for horizontal hit.
// When it hits a wall the loop breaks.
// Lastly it calculates the distance to the wall. */
static void	dda(t_raycaster *rc)
{
	while (1)
	{
		if (rc->s_dist_x < rc->s_dist_y)
		{
			rc->s_dist_x += rc->d_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->s_dist_y += rc->d_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (rc->map[rc->map_y][rc->map_x] == 1)
			break ;
	}
	if (rc->side == 0)
		rc->pwd = (rc->s_dist_x - rc->d_dist_x);
	else
		rc->pwd = (rc->s_dist_y - rc->d_dist_y);
}

// First calculate the camera x position. Then calculate the ray direction
// and the map position. Then calculate the delta distance and the step size.
// Then do the DDA and calculate the distance to the wall.
// Then calculate the wall height and the start and end positions for the wall.
// Then calculate the step size and x position on the texture.
// Then draw the wall.
static void	cast_single_ray(t_raycaster *rc)
{
	rc->cx = 2 * rc->x / (double)rc->screen_width - 1;
	rc->rdx = rc->pdx + rc->cpx * rc->cx;
	rc->rdy = rc->pdy + rc->cpy * rc->cx;
	rc->map_x = (int)rc->px;
	rc->map_y = (int)rc->py;
	delta_distance_calculation(rc);
	step_calculation(rc);
	dda(rc);
	prepare_for_drawing(rc);
	prepare_for_texture(rc);
	draw_textured_walls(rc);
}

// Cast a ray for every x position on the screen.
void	raycast(t_raycaster *rc)
{
	rc->x = 0;
	while (rc->x < rc->screen_width)
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)rc->py][(int)(rc->px + move_x)] == 0)
			rc->px += move_x;
		if (rc->map[(int)(rc->py + move_y)][(int)rc->px] == 0)
			rc->py += move_y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)rc->py][(int)(rc->px - move_x)] == 0)
			rc->px -= move_x;
		if (rc->map[(int)(rc->py - move_y)][(int)rc->px] == 0)
			rc->py -= move_y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		double oldDirX = rc->pdx;
		rc->pdx = rc->pdx * cos(-rotationSpeed) - rc->pdy * sin(-rotationSpeed);
		rc->pdy = oldDirX * sin(-rotationSpeed) + rc->pdy * cos(-rotationSpeed);
		double oldPlaneX = rc->cpx;
		rc->cpx = rc->cpx * cos(-rotationSpeed) - rc->cpy * sin(-rotationSpeed);
		rc->cpy = oldPlaneX * sin(-rotationSpeed) + rc->cpy * cos(-rotationSpeed);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = rc->pdx;
		rc->pdx = rc->pdx * cos(rotationSpeed) - rc->pdy * sin(rotationSpeed);
		rc->pdy = oldDirX * sin(rotationSpeed) + rc->pdy * cos(rotationSpeed);
		double oldPlaneX = rc->cpx;
		rc->cpx = rc->cpx * cos(rotationSpeed) - rc->cpy * sin(rotationSpeed);
		rc->cpy = oldPlaneX * sin(rotationSpeed) + rc->cpy * cos(rotationSpeed);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Q))
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)(rc->py - move_x)][(int)rc->px] == 0)
			rc->py -= move_x;
		if (rc->map[(int)rc->py][(int)(rc->px + move_y)] == 0)
			rc->px += move_y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_E))
	{
		printf("px: %f, py: %f\n", rc->px, rc->py);
		if (rc->map[(int)(rc->py + move_x)][(int)rc->px] == 0)
			rc->py += move_x;
		if (rc->map[(int)rc->py][(int)(rc->px - move_y)] == 0)
			rc->px -= move_y;
	}
	draw(*rc);
	draw_map(*rc);
	draw_player(*rc);
	printf("delta_time: %f\n", mlx->delta_time);
}

// -----------------------------------------------------------------------------

int	main(int argc, char *argv[])
{
	t_raycaster	rc;

	rc = init_raycaster();
	if (!rc.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	texture[0] = mlx_load_png("mario2.png");
	texture[1] = mlx_load_png("stone.png");
	texture[2] = mlx_load_png("archer.png");
	texture[3] = mlx_load_png("wt_logo.png");
	if (!(rc.screen = mlx_new_image(rc.mlx, rc.screen_width, rc.screen_height)) || !(rays = mlx_new_image(rc.mlx, rc.map_width * rc.tile_size, rc.map_height * rc.tile_size)))
	{
		mlx_close_window(rc.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	draw(rc);
	draw_map(rc);
	draw_player(rc);
	if (mlx_image_to_window(rc.mlx, rc.screen, 0, 0) == -1 || mlx_image_to_window(rc.mlx, rays, 0, 0) == -1)
	{
		mlx_close_window(rc.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(rc.mlx, ft_hook, &rc);
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	free_map(rc, rc.map);
	return (EXIT_SUCCESS);
}
