/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:01:22 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 21:15:38 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			sign;
	long int	atoi;
	long int	buf;

	atoi = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ' )
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		buf = atoi;
		atoi = atoi * 10 + *str - '0';
		if (atoi / 10 != buf && sign == -1)
			return (0);
		else if (atoi / 10 != buf && sign == 1)
			return (-1);
		str++;
	}
	return (sign * atoi);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*   Atoi converts the initial portion of the string pointed to by str to int */
/*   representation.                                                          */
/*                                                                            */
/*RETURN VALUES                                                               */
/*   Atoi returns the integer value represented by the parsed string.         */
/*   If the string does not contain a valid integer, it returns 0.            */
/*                                                                            */
/*FUNCTION EXECUTION                                                          */
/*   Parses the string until it encounters the first non-numeric character    */
/*   or the end of the string.                                                */
/*   Ignores leading whitespace characters.                                   */
/*   Stops parsing when encountering the first non-numeric character.         */
/*                                                                            */
/******************************************************************************/
