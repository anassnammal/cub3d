/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:47:27 by anammal           #+#    #+#             */
/*   Updated: 2024/03/06 23:57:50 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *s)
{
	static char	*buff;
	char		*token;

	if (s)
		buff = s;
	if (!buff)
		return (NULL);
	while (ft_isspace(*buff))
		buff++;
	if (!*buff)
		return (NULL);
	token = buff;
	while (*buff && !ft_isspace(*buff))
		buff++;
	*buff++ = 0;
	return (token);
}