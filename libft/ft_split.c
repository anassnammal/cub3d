/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:42:36 by anammal           #+#    #+#             */
/*   Updated: 2024/01/07 09:26:57 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skiper(char *s, char d, int o)
{
	if (o)
	{
		while (*s && *s == d)
			s++;
	}
	else
	{
		while (*s != d && *s)
			s++;
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;

	strs = (char **)ft_calloc(2, sizeof(char *));
	if (strs)
	{
		i = 0;
		while (*s)
		{
			s = skiper((char *)s, c, 1);
			*(strs + i) = ft_substr(s, 0, ft_strdlen((char *)s, c));
			if (!*(strs + i))
				return (ft_strsfree(strs), NULL);
			strs = (char **)ft_realloc((void **)strs, ++i + 1, 1);
			if (!strs)
				return (ft_strsfree(strs), NULL);
			s = skiper((char *)s, c, 0);
		}
		*(strs + i) = NULL;
	}
	return (strs);
}
