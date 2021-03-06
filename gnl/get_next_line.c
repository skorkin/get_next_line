/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzelda <bzelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 07:17:12 by bzelda            #+#    #+#             */
/*   Updated: 2020/12/05 03:00:46 by bzelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"

static int		buff_free(char **buff)
{
	if (*buff != NULL)
		free(*buff);
	*buff = NULL;
	return (0);
}

static char		*buff_create(char *buff)
{
	if (buff == NULL)
	{
		if (!(buff = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (NULL);
		buff[0] = '\0';
	}
	return (buff);
}

static char		*buff_cut_c(char *buff, char c)
{
	char		*res;
	int32_t		i;
	int32_t		j;

	res = NULL;
	if (!(res = buff_create(res)))
		return (NULL);
	i = 0;
	while (buff[i] != '\0' && buff[i] != c)
		i++;
	if (buff[i] == '\0')
	{
		res[0] = buff[i];
		return (res);
	}
	i++;
	j = 0;
	while (buff[i] != '\0')
		res[j++] = buff[i++];
	res[j] = '\0';
	free(buff);
	return (res);
}

int				take_str(char **line, char **buff)
{
	*line = my_strjoin_c(*line, *buff, '\n');
	if (*line == NULL)
		return (-1);
	if (my_strchr(*buff, '\n'))
	{
		*buff = buff_cut_c(*buff, '\n');
		if (*buff == NULL)
			return (-1);
		return (1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char		*buff[1024];
	int32_t			read_count;
	int32_t			tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (!(*line = my_strjoin_c(NULL, "\0", '\0')))
		return (-1);
	if (!(buff[fd] = buff_create(buff[fd])))
		return (buff_free(&(buff[fd])) - 1);
	if (buff[fd][0] != '\0')
	{
		if ((take_str(line, &(buff[fd]))))
			return (1);
	}
	while ((read_count = read(fd, buff[fd], BUFFER_SIZE)) > 0 && tmp != -1)
	{
		buff[fd][read_count] = '\0';
		if ((tmp = take_str(line, &buff[fd])) == 1)
			return (1);
	}
	if (read_count < 0 || tmp == -1)
		return (buff_free(&(buff[fd])) - 1);
	return (buff_free(&(buff[fd])));
}
