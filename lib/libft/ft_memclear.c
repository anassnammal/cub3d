/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:00:12 by anammal           #+#    #+#             */
/*   Updated: 2024/01/07 09:11:06 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memclear(void **ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(*(ptr + i));
		*(ptr + i) = NULL;
		i++;
	}
	free(ptr);
}
