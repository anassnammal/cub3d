/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:48:39 by anammal           #+#    #+#             */
/*   Updated: 2024/01/07 09:25:39 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_realloc(void **t, size_t l, size_t p)
{
	void	**new;
	size_t	i;

	if (p == 0)
		return (t);
	new = ft_calloc(sizeof(void *), (l + p));
	if (new)
	{
		i = -1;
		while (++i < l)
			*(new + i) = *(t + i);
		ft_bzero(t, sizeof(void *) * l);
		return (free(t), new);
	}
	return (NULL);
}
