/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:23:19 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/23 20:05:05 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	parser_error_handler(int error)
{
	if (error == 0)
		ft_putstr_fd("Error while opening file.", 2);
	if (error == 1)
		ft_putstr_fd("Error while mallocing space.", 2);
	exit(1);
}

static int	is_line_valid(char *line)
{
	char	**line_arg;
	int		ret;

	ret = 0;
	line_arg = ft_strsplit(line, ' ');
	if (line_arg == NULL)
		parser_error_handler(1);
	if (line_arg[0] != NULL)
	{
		if (strcmp(line_arg[0], "sphere") == 0)
			if (check_sphere(line_arg) == 1)
				ret = 1;
		if (strcmp(line_arg[0], "plane") == 0)
			if (check_plane(line_arg) == 1)
				ret = 1;
		if (strcmp(line_arg[0], "cylinder") == 0)
			if (check_cylinder(line_arg) == 1)
				ret = 1;
		if (strcmp(line_arg[0], "cone") == 0)
			if (check_cone(line_arg) == 1)
				ret = 1;
		ft_arrdel(line_arg);
	}
	return (ret);
}

static int	read_and_store(char **argv,t_rtv *rtv)
{
	int		ret;
	int		fd;
	char	*line;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		parser_error_handler(0);
	ret = 1;
	i = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == 1 && (is_line_valid(line) == 1 || strncmp(line, "light", ft_strlen("light")) == 0))
		{
			fill_shape(rtv, line, i);
			ft_strdel(&line);
			i++;
		}
		else if (ret == 1)
			ft_strdel(&line);
	}
	close(fd);
	if (ret == -1)
		return (-1);
	return (1);
}

static int	shape_counter(char **argv, t_rtv *rtv)
{
	int		ret;
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		parser_error_handler(0);
	rtv->shape_count = 0;
	ret = 1;
	while (ret == 1)
	{
		
		ret = get_next_line(fd, &line);
		if (ret == 1 && is_line_valid(line) == 1)
		{
			ft_strdel(&line);
			rtv->shape_count++;
		}
		else if (ret == 1)
			ft_strdel(&line);
	}
	close(fd);
	if (ret == -1)
		return (-1);
	return (1);
}

int		read_imput(char **argv, t_rtv *rtv)
{
	if (shape_counter(argv, rtv) == -1)
		parser_error_handler(1);
	rtv->shape = (t_shape *)malloc(sizeof(t_shape) * rtv->shape_count);
	if (rtv->shape == NULL)
		parser_error_handler(1);
	read_and_store(argv, rtv);
	return (1);
}