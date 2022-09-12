/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:09 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/12 15:29:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	draw_to_window(t_rtv *rtv)
{
	int		*texture_data;
	int		texture_pitch;

	if (SDL_LockTexture(rtv->texture, NULL, (void **)&texture_data,
			&texture_pitch) < 0)
	{
		exit(1);
	}
	ft_memcpy(texture_data, rtv->frame_buffer.data,
		(rtv->frame_buffer.data_len * sizeof(int)));
	SDL_UnlockTexture(rtv->texture);
	if (SDL_RenderCopy(rtv->ren, rtv->texture, NULL, NULL) < 0)
	{
		exit(1);
	}
	SDL_RenderPresent(rtv->ren);
}

void	rtv_loop_and_exit(t_rtv	*rtv)
{
	int	quit;

	quit = 0;
	while (quit == 0)
	{
		while (SDL_PollEvent(&rtv->event))
		{
			if (rtv->event.type == SDL_QUIT)
				quit = 1;
			if (rtv->event.type == SDL_KEYDOWN)
				if (rtv->event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
			if (rtv->event.type == SDL_KEYDOWN)
				if (rtv->event.key.keysym.sym == SDLK_r)
					draw_to_window(rtv);
		}
	}
	SDL_DestroyTexture(rtv->texture);
	SDL_DestroyWindow(rtv->win);
	free(rtv->frame_buffer.data);
	free(rtv->shape);
}

int	create_rtv_struct(t_rtv	*rtv)
{
	rtv->win = SDL_CreateWindow("rtv1", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (rtv->win == NULL)
		return (0);
	rtv->ren = SDL_CreateRenderer(rtv->win, -1, 0);
	if (rtv->ren == NULL)
		return (0);
	rtv->texture = SDL_CreateTexture(rtv->ren, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (rtv->texture == NULL)
		return (0);
	rtv->frame_buffer.data_len = (WIN_H * WIN_W);
	rtv->frame_buffer.data = (int *)malloc(sizeof(int)
			* rtv->frame_buffer.data_len);
	rtv->camera.pos.x = 0.0;
	rtv->camera.pos.y = 0.0;
	rtv->camera.pos.z = 0.0;
	rtv->camera.coi.x = 0.0;
	rtv->camera.coi.y = 0.0;
	rtv->camera.coi.z = 10.0;
	rtv->camera.v_up.x = 0.0;
	rtv->camera.v_up.y = 10.0;
	rtv->camera.v_up.z = 0.0;
	return (1);
}

void	print_usage(void)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open("usage.txt", O_RDONLY);
	while (ret == 1 && fd > -1)
	{
		ret = get_next_line(fd, &line);
		if (ret == 1)
		{
			ft_putendl(line);
			ft_strdel(&line);
		}
	}
	if (fd > -1)
		close(fd);
}

int	main(int argc, char **argv)
{
	t_rtv	rtv;

	if (argc != 2 && argv != NULL)
	{
		print_usage();
		return (1);
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if (create_rtv_struct(&rtv) == 0)
		return (1);
	read_imput(argv, &rtv);
	render_image(&rtv);
	draw_to_window(&rtv);
	rtv_loop_and_exit(&rtv);
	SDL_Quit();
	return (0);
}
