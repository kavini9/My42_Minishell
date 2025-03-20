/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:26:41 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/19 16:09:34 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

void	putstr_fd(char *str, int *totlen, int fd)
{
	if (!str)
		str = "(nil)";
	while (*str && *totlen != -1)
		putchar_fd(*str++, totlen, fd);
}
