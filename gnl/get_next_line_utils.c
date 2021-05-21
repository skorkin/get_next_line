/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzelda <bzelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 07:23:46 by bzelda            #+#    #+#             */
/*   Updated: 2020/12/04 04:25:39 by bzelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

static size_t	my_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

static size_t	my_strlen_c(char *s, char c)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

char			*my_strchr(char *s, char c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

char			*my_strjoin_c(char *s1, char *s2, char c)
{
	t_str	res;
	size_t	i;

	res.len = my_strlen(s1) + my_strlen_c(s2, '\n');
	res.s = (char*)malloc(sizeof(char) * (res.len + 1));
	if (res.s == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while ((s1 + ++i) != NULL && s1[i] != '\0')
		res.s[i] = s1[i];
	while (s2 != NULL && *s2 != '\0' && *s2 != c)
	{
		res.s[i] = *s2;
		s2++;
		i++;
	}
	res.s[i] = '\0';
	free(s1);
	return (res.s);
}
