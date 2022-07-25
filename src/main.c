/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:09 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/25 13:24:45 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	rtv_loop_and_exit(t_rtv	*rtv)
{
	int quit;

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
		}
		SDL_DestroyTexture(rtv->texture);
	}
	SDL_DestroyWindow(rtv->win);
	free(rtv->frame_buffer.data);
}

void    draw_to_window(t_rtv *rtv)
{
	int    *texture_data;
	int    texture_pitch;

	if (SDL_LockTexture(rtv->texture, NULL, (void **)&texture_data,
			&texture_pitch) < 0)
	{
		ft_putstr("hello1\n");
	}
	ft_memcpy(texture_data, rtv->frame_buffer.data,
		(rtv->frame_buffer.data_len * sizeof(int)));
	SDL_UnlockTexture(rtv->texture);
	if (SDL_RenderCopy(rtv->ren, rtv->texture, NULL, NULL) < 0)
	{
		ft_putstr("hello\n");
	}
	SDL_RenderPresent(rtv->ren);
}

int		create_rtv_struct(t_rtv	*rtv)
{
	rtv->win =SDL_CreateWindow("rtv1",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED , WIN_W,WIN_H,0);
	if (rtv->win == NULL)
		return (0);
	rtv->ren = SDL_CreateRenderer(rtv->win, -1, 0);
	if (rtv->ren == NULL)
		return (0);
	rtv->texture = SDL_CreateTexture(rtv->ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (rtv->texture == NULL)
		return (0);
	rtv->frame_buffer.data_len = (WIN_H * WIN_W);
	rtv->frame_buffer.data = (int *)malloc(sizeof(int) * rtv->frame_buffer.data_len);
	
	
	rtv->camera.x = 0.0;
	rtv->camera.y = 0.0;
	rtv->camera.z = 0.0;
	
	rtv->shape[0].type = 's';
	rtv->shape[0].pos.x = 0.0;
	rtv->shape[0].pos.y = 0.0;
	rtv->shape[0].pos.z = 1000.0;
	rtv->shape[0].color = 0xff000000;
	rtv->shape[0].r = 5.0;

	rtv->shape[8].type = 's';
	rtv->shape[8].pos.x = 1.00;
	rtv->shape[8].pos.y = 0.00;
	rtv->shape[8].pos.z = -900.0;
	rtv->shape[8].color = 0xffff0000;
	rtv->shape[8].r = 1.0;

	rtv->shape[1].type = 'c';
	rtv->shape[1].pos.x = -10.0;
	rtv->shape[1].pos.y = 2.0;
	rtv->shape[1].pos.z = 0.0;
	rtv->shape[1].cyl_h.x = -0.40;
	rtv->shape[1].cyl_h.y = 0.0;
	rtv->shape[1].cyl_h.z = 1000.0;
	rtv->shape[1].r = 0.60;
	rtv->shape[1].color = 0x0000ff00;
	
	rtv->shape[2].type = 'c';
	rtv->shape[2].pos.x = 10.0;
	rtv->shape[2].pos.y = 2.0;
	rtv->shape[2].pos.z = 0.0;
	rtv->shape[2].cyl_h.x = 0.40;
	rtv->shape[2].cyl_h.y = 0.0;
	rtv->shape[2].cyl_h.z = 1000.0;
	rtv->shape[2].r = 0.60;
	rtv->shape[2].color = 0x00ffff00;
	
	rtv->shape[3].type = 'c';
	rtv->shape[3].pos.x = 0.0;
	rtv->shape[3].pos.y = -10.0;
	rtv->shape[3].pos.z = 0.0;
	rtv->shape[3].cyl_h.x = 0.0;
	rtv->shape[3].cyl_h.y = -1.0;
	rtv->shape[3].cyl_h.z = 1000.0;
	rtv->shape[3].r = 0.60;
	rtv->shape[3].color = 0xffff0000;
	
	//rtv->shape[2].type = 'c';
	//rtv->shape[2].pos.x = 0.0;
	//rtv->shape[2].pos.y = 0.0;
	//rtv->shape[2].pos.z = 1000.0;
	//rtv->shape[2].cyl_h.x = 1.0;
	//rtv->shape[2].cyl_h.y = 10.0;
	//rtv->shape[2].cyl_h.z = 1000.0;
	//rtv->shape[2].r = 0.050;
	//rtv->shape[2].color = 0x0000ff00;
	
	//rtv->shape[2].type = 's';
	//rtv->shape[2].pos.x = 7.0;
	//rtv->shape[2].pos.y = 4.00;
	//rtv->shape[2].pos.z = 1000.00;
	//rtv->shape[2].r = 1;
	//rtv->shape[2].color = 0x00ff0000;
	//
	
	rtv->shape[4].type = 'p';
	rtv->shape[4].pos.x = 10.0;
	rtv->shape[4].pos.y = 0.00;
	rtv->shape[4].pos.z = 1000.0;
	rtv->shape[4].cyl_h.x = 1.0;
	rtv->shape[4].cyl_h.y = 0.0;
	rtv->shape[4].cyl_h.z = 0.0;
	rtv->shape[4].color = 0xff00ff00;

	rtv->shape[5].type = 'p';
	rtv->shape[5].pos.x = -10.0;
	rtv->shape[5].pos.y = 0.00;
	rtv->shape[5].pos.z = 1000.0;
	rtv->shape[5].cyl_h.x = -1.0;
	rtv->shape[5].cyl_h.y = 0.0;
	rtv->shape[5].cyl_h.z = 0.0;
	rtv->shape[5].color = 0x0ff0ff00;

	rtv->shape[6].type = 'p';
	rtv->shape[6].pos.x = 0.0;
	rtv->shape[6].pos.y = 10.00;
	rtv->shape[6].pos.z = 1000.0;
	rtv->shape[6].cyl_h.x = 0.0;
	rtv->shape[6].cyl_h.y = 1.0;
	rtv->shape[6].cyl_h.z = 0.0;
	rtv->shape[6].color = 0x00ab0ff00;

	rtv->shape[7].type = 'p';
	rtv->shape[7].pos.x = 0.0;
	rtv->shape[7].pos.y = -10.00;
	rtv->shape[7].pos.z = 1000.0;
	rtv->shape[7].cyl_h.x = 0.0;
	rtv->shape[7].cyl_h.y = -1.0;
	rtv->shape[7].cyl_h.z = 0.0;
	rtv->shape[7].color = 0xaf00ff00;

	rtv->shape_count = 9;


	rtv->light.pos.x = 100.0;
	rtv->light.pos.y = 0.0;
	rtv->light.pos.z = 1000.0;

	
	return (1);
}

int		main(void)
{
	
	t_rtv	rtv;

	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
		return (1);
	if (create_rtv_struct(&rtv) == 0)
		return (1);
	
	render_image(&rtv);
	draw_to_window(&rtv);
	rtv_loop_and_exit(&rtv);
	SDL_Quit();
	return 0;
}