/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:43:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/14 23:52:32 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include "minishell.h"

# define ERR_SYNTAX "syntax error near unexpected token near %s\n"
# define ERR_MALLOC "minishell: fatal error: memory allocation failed in %s.\n"
# define ERR_DIR_NOTSET "minishell: cd: %s not set.\n"
# define ERR_DIR_UNLINK "minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n"
# define ERR_GETCWD "minishell: %s: error retrieving current directory: getcwd: %s\n"
# define ERR_CHDIR "minishell: cd: %s: %s.\n"

#endif