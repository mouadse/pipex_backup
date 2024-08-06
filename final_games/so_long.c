/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:50:21 by msennane          #+#    #+#             */
/*   Updated: 2024/08/06 13:31:24 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_game_state *state)
{
	if (keycode == ESC_KEY)
	{
		cleanup_game_resources(state);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == UP_KEY_W || keycode == UP_KEY_ARROW)
	{
		move_sprite_up(state);
	}
	else if (keycode == LEFT_KEY_A || keycode == LEFT_KEY_ARROW)
	{
		move_sprite_left(state);
	}
	else if (keycode == DOWN_KEY_S || keycode == DOWN_KEY_ARROW)
	{
		move_sprite_down(state);
	}
	else if (keycode == RIGHT_KEY_D || keycode == RIGHT_KEY_ARROW)
	{
		move_sprite_right(state);
	}
	return (0);
}

int	handle_window_close(t_game_state *state)
{
	cleanup_game_resources(state);
	exit(EXIT_SUCCESS);
}

int	update_window(t_game_state *state)
{
	static int	prev_player_col = -1;
	static int	prev_player_row = -1;

	if (state->game_completed && state->player.col == state->level_exit.col
		&& state->player.row == state->level_exit.row)
	{
		ft_printf("Congratulations You have completed the game!\n");
		cleanup_game_resources(state);
		exit(EXIT_SUCCESS);
	}
	if (prev_player_col != state->player.col
		|| prev_player_row != state->player.row)
	{
		mlx_clear_window(state->mlx_instance, state->window_instance);
		render_game_map(state);
		render_player(state);
		prev_player_col = state->player.col;
		prev_player_row = state->player.row;
	}
	return (0);
}

static void	init_map_res(t_game_state *state)
{
	state->assets.closed_door_asset = NULL;
	state->assets.coin_asset = NULL;
	state->assets.floor_asset = NULL;
	state->assets.open_door_asset = NULL;
	state->assets.wall_asset = NULL;
	state->player.spirites[0] = NULL;
	state->player.spirites[1] = NULL;
	state->player.spirites[2] = NULL;
	state->player.spirites[3] = NULL;
}

int	main(int argc, char **argv)
{
	t_game_state	state;

	init_map_res(&state);
	if (process_arguments_and_map(argc, argv, &state))
	{
		state.mlx_instance = mlx_init();
		if (!state.mlx_instance)
			return (cleanup_game_resources(&state), 1);
		state.window_instance = mlx_new_window(state.mlx_instance,
				state.map.cols * 32, state.map.rows * 32, "so_long");
		if (!state.window_instance)
			return (cleanup_game_resources(&state), 1);
		init_player_images(&state);
		load_game_textures(&state);
		verify_textures_loaded(&state);
		mlx_hook(state.window_instance, KeyPress, KeyPressMask, handle_keypress,
			&state);
		mlx_loop_hook(state.mlx_instance, update_window, &state);
		mlx_hook(state.window_instance, DestroyNotify, StructureNotifyMask,
			handle_window_close, &state);
		mlx_loop(state.mlx_instance);
	}
	free_map_layout(&state.map);
	return (EXIT_SUCCESS);
}
