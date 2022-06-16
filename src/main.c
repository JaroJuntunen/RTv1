/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:09 by jjuntune          #+#    #+#             */
/*   Updated: 2022/06/16 19:32:13 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	RTv_Loop_and_Exit(t_RTv	*RTv)
{
	int quit;

	quit = 0;
	while (quit == 0)
	{
		while (SDL_PollEvent(&RTv->event))
		{
			if (RTv->event.type == SDL_QUIT)
				quit = 1;
			if (RTv->event.type == SDL_KEYDOWN)
				if (RTv->event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
		}
	}
	SDL_DestroyWindow(RTv->win);
}

int		Create_RTv_struct(t_RTv	*RTv)
{
	RTv->win = NULL;
	if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_SHOWN,
		&RTv->win, &RTv->ren) == -1)
		return (0);
	RTv->texture = SDL_CreateTexture(RTv->ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIN_W, WIN_H);
	if (RTv->texture == NULL)
		return (0);
	RTv->frame_buffer.data_len = WIN_H * WIN_W;
	RTv->frame_buffer.data = (int *)malloc(sizeof(int) * RTv->frame_buffer.data_len);
	RTv->camera.x = 0;
	RTv->camera.y = 0;
	RTv->camera.z = 100;
	RTv->shape[0].type = 's';
	RTv->shape[0].pos.x = 100;
	RTv->shape[0].pos.y = 100;
	RTv->shape[0].pos.z = 100;
	RTv->shape[0].r = 20;
	RTv->shape[0].color = 0xff0000;
	RTv->shape_count = 1;
	return (1);
}

int		main(void)
{
	
	t_RTv	RTv;
	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
		return (1);
	if (Create_RTv_struct(&RTv) == 0)
		return (1);
	Render_Image(&RTv);
	RTv_Loop_and_Exit(&RTv);
	SDL_Quit();
	return 0;
}