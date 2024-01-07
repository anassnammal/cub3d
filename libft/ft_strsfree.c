/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:00:12 by anammal           #+#    #+#             */
/*   Updated: 2024/01/07 09:32:49 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsfree(char **strs)
{
	int	i;

	i = 0;
	while (*(strs + i) != NULL)
	{
		ft_bzero(strs, ft_strlen(*(strs + i)));
		free(*(strs + i));
		*(strs + i) = NULL;
		i++;
	}
	free(strs);
}
