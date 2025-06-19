/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:26:41 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/19 15:58:06 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

void	putstr_fd(char *str, int *totlen, int fd)
{
	int	len;

	if (!str)
		str = "(nil)";
	len = ft_strlen(str);
	if (write(fd, str, len) == -1)
		*totlen = -1;
	else
		(*totlen) += len;
}
