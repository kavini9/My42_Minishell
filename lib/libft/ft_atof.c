/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:04:06 by wweerasi          #+#    #+#             */
/*   Updated: 2024/10/26 17:25:20 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	int			sign;
	double		atof;
	double		div;

	atof = 0.0;
	div = 0.1;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str) == 1)
		atof = (atof * 10.0) + *str++ - '0';
	if (*str == '.')
		str++;
	while (*str && ft_isdigit(*str) == 1)
	{
		atof = atof + ((*str++ - '0') * div);
		div = div * 0.1;
	}
	return (sign * atof);
}
