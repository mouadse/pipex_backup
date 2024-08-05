/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:50:09 by msennane          #+#    #+#             */
/*   Updated: 2024/08/05 13:04:09 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdbool.h>

int	valid_move(t_game_state *state, int row, int col)
{
	if (row < 0 || row > state->map.rows - 1 || col < 0 || col > state->map.cols
		- 1)
		return (0);
	if (state->map.layout[row][col] == '1')
		return (0);
	if (state->map.layout[row][col] == 'E' && state->game_completed == 0)
		return (0);
	return (1);
}

void	move_sprite_up(t_game_state *state)
{
	if (valid_move(state, state->player.row - 1, state->player.col))
	{
		state->player.row -= 1;
		state->player.moves_count += 1;
		state->player.facing_direction = 0;
		if (state->map.layout[state->player.row][state->player.col] == 'C')
		{
			state->player.score += 10;
			state->map.layout[state->player.row][state->player.col] = '0';
		}
		if (state->player.score == state->map.total_collectibles * 10)
		{
			state->game_completed = 1;
			state->map.is_exit_open = true;
		}
		ft_printf("Moves %d\n", state->player.moves_count);
	}
}

void	move_sprite_down(t_game_state *state)
{
	if (valid_move(state, state->player.row + 1, state->player.col))
	{
		state->player.row += 1;
		state->player.moves_count += 1;
		state->player.facing_direction = 2;
		if (state->map.layout[state->player.row][state->player.col] == 'C')
		{
			state->player.score += 10;
			state->map.layout[state->player.row][state->player.col] = '0';
		}
		if (state->player.score == state->map.total_collectibles * 10)
		{
			state->game_completed = 1;
			state->map.is_exit_open = true;
		}
		ft_printf("Moves %d\n", state->player.moves_count);
	}
}

void	move_sprite_right(t_game_state *state)
{
	if (valid_move(state, state->player.row, state->player.col + 1))
	{
		state->player.col += 1;
		state->player.moves_count += 1;
		state->player.facing_direction = 3;
		if (state->map.layout[state->player.row][state->player.col] == 'C')
		{
			state->player.score += 10;
			state->map.layout[state->player.row][state->player.col] = '0';
		}
		if (state->player.score == state->map.total_collectibles * 10)
		{
			state->game_completed = 1;
			state->map.is_exit_open = true;
		}
		ft_printf("Moves %d\n", state->player.moves_count);
	}
}

void	move_sprite_left(t_game_state *state)
{
	if (valid_move(state, state->player.row, state->player.col - 1))
	{
		state->player.col -= 1;
		state->player.moves_count += 1;
		state->player.facing_direction = 1;
		if (state->map.layout[state->player.row][state->player.col] == 'C')
		{
			state->player.score += 10;
			state->map.layout[state->player.row][state->player.col] = '0';
		}
		if (state->player.score == state->map.total_collectibles * 10)
		{
			state->game_completed = 1;
			state->map.is_exit_open = true;
		}
		ft_printf("Moves %d\n", state->player.moves_count);
	}
}
