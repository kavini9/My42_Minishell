/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:18:41 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/19 17:38:36 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

void	putchar_fd(char c, int *totlen, int fd)
{
	if (write(fd, &c, 1) == -1)
		*totlen = -1;
	else
		(*totlen)++;
}
