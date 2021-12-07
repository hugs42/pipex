/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:45:21 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/29 10:57:40 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	int				i;
	static char		*stock;

	i = 0;
	if (str != NULL)
		stock = str;
	if (!(stock) || (!(*stock)))
		return (NULL);
	while (!(ft_strchr(delim, stock[i])))
		i++;
	str = stock;
	stock = &stock[i];
	if (!i)
		return (ft_strtok(stock + 1, delim));
	if (str[i])
		stock += 1;
	str[i] = '\0';
	return (str);
}
