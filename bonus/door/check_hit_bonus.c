/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 05:47:37 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/10 11:53:27 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This file contain the primary function to handle doors properly
 *
 * The door code is as follow :
 * c : closed door (bottom of block)
 * o : open   door (right  of block)
 * C : CLOSED door (top    of block)
 * O : OPEN   door (left   of block)
 */

#include "../../includes/cub3d.h"

/**
 * @brief Reduce ray->side_dist when door was hit from inside the block
 *
 * This function reduce the ray->side value when a door was hitted from inside
 * It is needed to reduce the perp_wall_dist to render 'realisic' doors
 *
 * @param	ray		The ray we're actually working with
 */
static void	correct_perp_wall_dist(t_raycast *ray)
{
	double	angle;
	double	h_pos_len;

	h_pos_len = sqrtf(ray->h_pos.x * ray->h_pos.x
		+ (ray->h_pos.y * ray->h_pos.y));
	if (ray->side == 1)
	{
		angle = 0.05 * (ray->h_pos.x / h_pos_len);
		ray->side_dist.x -= 0.05 / angle;
		return ;
	}
	angle = 0.05 * (ray->h_pos.y / h_pos_len);
	ray->side_dist.y -= 0.05 / angle;
}

/**
 * @brief Check if something was hit in the North-West direction
 * 
 * Check if a door was hit in the North West direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_north_west(t_data *data, t_raycast *ray)
{
	if (ray->side == 1)
	{
		if (data->map[ray->map.x][ray->map.y - 1] == 'C')
			return (correct_perp_wall_dist(ray), 'C');
		if (data->map[ray->map.x][ray->map.y] == 'c')
			return ('c');
		if (data->map[ray->map.x][ray->map.y] == 'o'
				&& ray->h_pos.x - (int)ray->map.x <= 0.05)
			return ('o');
		if (data->map[ray->map.x][ray->map.y] == 'O'
				&& ray->h_pos.x - (int)ray->map.x >= 0.95)
			return ('O');
		return (data->map[ray->map.x][ray->map.y] == '1');
	}
	if (data->map[ray->map.x + 1][ray->map.y] == 'O')
		return (correct_perp_wall_dist(ray), 'O');
	if (data->map[ray->map.x][ray->map.y] == 'o')
		return ('o');
	if (data->map[ray->map.x][ray->map.y] == 'c'
			&& ray->h_pos.y - (int)ray->map.y <= 0.05)
		return ('c');
	if (data->map[ray->map.x][ray->map.y] == 'C'
			&& ray->h_pos.y - (int)ray->map.y >= 0.95)
		return ('C');
	return (data->map[ray->map.x][ray->map.y] == '1');
}

/**
 * @brief Check if something was hit in the North-Est direction
 * 
 * Check if a door was hit in the North Est direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_north_est(t_data *data, t_raycast *ray)
{
	if (ray->side == 1)
	{
		if (data->map[ray->map.x][ray->map.y - 1] == 'C')
			return (correct_perp_wall_dist(ray), 'C');
		if (data->map[ray->map.x][ray->map.y] == 'c')
			return ('c');
		if (data->map[ray->map.x][ray->map.y] == 'o'
				&& ray->h_pos.x - (int)ray->map.x <= 0.05)
			return ('o');
		if (data->map[ray->map.x][ray->map.y] == 'O'
				&& ray->h_pos.x - (int)ray->map.x >= 0.95)
			return ('O');
		return (data->map[ray->map.x][ray->map.y] == '1');
	}
	if (data->map[ray->map.x - 1][ray->map.y] == 'o')
		return (correct_perp_wall_dist(ray), 'o');
	if (data->map[ray->map.x][ray->map.y] == 'O')
		return ('O');
	if (data->map[ray->map.x][ray->map.y] == 'c'
			&& ray->h_pos.y - (int)ray->map.y <= 0.05)
		return ('c');
	if (data->map[ray->map.x][ray->map.y] == 'C'
			&& ray->h_pos.y - (int)ray->map.y >= 0.95)
		return ('C');
	return (data->map[ray->map.x][ray->map.y] == '1');

}

/**
 * @brief Check if something was hit in the South-Est direction
 * 
 * Check if a door was hit in the South Est direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_south_est(t_data *data, t_raycast *ray)
{
	if (ray->side == 1)
	{
		if (data->map[ray->map.x][ray->map.y + 1] == 'c')
			return (correct_perp_wall_dist(ray), 'c');
		if (data->map[ray->map.x][ray->map.y] == 'C')
			return ('C');
		if (data->map[ray->map.x][ray->map.y] == 'o'
				&& ray->h_pos.x - (int)ray->map.x <= 0.05)
			return ('o');
		if (data->map[ray->map.x][ray->map.y] == 'O'
				&& ray->h_pos.x - (int)ray->map.x >= 0.95)
			return ('O');
		return (data->map[ray->map.x][ray->map.y] == '1');
	}
	if (data->map[ray->map.x - 1][ray->map.y] == 'o')
		return (correct_perp_wall_dist(ray), 'o');
	if (data->map[ray->map.x][ray->map.y] == 'O')
		return ('O');
	if (data->map[ray->map.x][ray->map.y] == 'c'
			&& ray->h_pos.y - (int)ray->map.y <= 0.05)
		return ('c');
	if (data->map[ray->map.x][ray->map.y] == 'C'
			&& ray->h_pos.y - (int)ray->map.y >= 0.95)
		return ('C');
	return (data->map[ray->map.x][ray->map.y] == '1');
}

/**
 * @brief Check if something was hit in the South-West direction
 * 
 * Check if a door was hit in the South West direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_south_west(t_data *data, t_raycast *ray)
{
	if (ray->side == 1)
	{
		if (data->map[ray->map.x][ray->map.y + 1] == 'c')
			return (correct_perp_wall_dist(ray), 'c');
		if (data->map[ray->map.x][ray->map.y] == 'C')
			return ('C');
		if (data->map[ray->map.x][ray->map.y] == 'o'
				&& ray->h_pos.x - (int)ray->map.x <= 0.05)
			return ('o');
		if (data->map[ray->map.x][ray->map.y] == 'O'
				&& ray->h_pos.x - (int)ray->map.x >= 0.95)
			return ('O');
		return (data->map[ray->map.x][ray->map.y] == '1');
	}
	if (data->map[ray->map.x + 1][ray->map.y] == 'O')
		return (correct_perp_wall_dist(ray), 'O');
	if (data->map[ray->map.x][ray->map.y] == 'o')
		return ('C');
	if (data->map[ray->map.x][ray->map.y] == 'c'
			&& ray->h_pos.y - (int)ray->map.y <= 0.05)
		return ('c');
	if (data->map[ray->map.x][ray->map.y] == 'C'
			&& ray->h_pos.y - (int)ray->map.y >= 0.95)
		return ('C');
	return (data->map[ray->map.x][ray->map.y] == '1');
}

/**
 * @brief Return an integer indicating the type of block the ray hit
 *
 * This funnction check what kind of block was hit, It is needed to properly
 * render door and walls. For norming purpose it is splitted into five function
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we'rte working with
 * @return	An integer indicating what block was hit ('c'/'C'/'o'/'O'/'1'/'0')
 */
int	check_hit(t_data *data, t_raycast *ray)
{
	get_hit_pos(data, ray);
	if (ray->dir.x < 0.0 && ray->dir.y < 0.0)
		return (check_south_west(data, ray));
	if (ray->dir.x < 0.0 && ray->dir.y >= 0.0)
		return (check_north_west(data, ray));
	if (ray->dir.x >= 0.0 && ray->dir.y < 0.0)
		return (check_south_est(data, ray));
	return (check_north_est(data, ray));
}
