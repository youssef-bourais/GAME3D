/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:59:01 by msodor            #+#    #+#             */
/*   Updated: 2023/08/03 10:03:08 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		signe;
	int		res;

	i = 0;
	res = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * signe);
}
