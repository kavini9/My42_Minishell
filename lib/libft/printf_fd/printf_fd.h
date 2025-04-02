/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:41:35 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/19 20:02:47 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FD_H
# define PRINTF_FD_H

# define DEC "0123456789"
# define HEX "0123456789abcdef"
# define HEX_U "0123456789ABCDEF"

# include <stdarg.h>
# include <unistd.h>

# include "../libft.h"

typedef struct s_base
{
	char		*str;
	int			base ;
}				t_base;

int		printf_fd(int fd, const char *format, ...);
void	putchar_fd(char c, int *totlen, int fd);
void	putnbr_fd(int nbr, t_base b, int *totlen, int fd);
void	putnbr_u_fd(unsigned long nbr, t_base b, int *totlen, int fd);
void	putstr_fd(char *str, int *totlen, int fd);

#endif
