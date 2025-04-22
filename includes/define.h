/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:43:40 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/22 00:09:02 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include "minishell.h"

# define ERR_SYNTAX "syntax error near unexpected token near %s\n"
# define ERR_MALLOC "minishell: fatal error: memory allocation failed in %s\n"
# define ERR_DIR_NOTSET "minishell: cd: %s not set\n"
# define ERR_DIR_UNLINK "minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n"
# define ERR_GETCWD "minishell: %s: error retrieving current directory: getcwd: %s\n"
# define ERR_CHDIR "minishell: cd: %s: %s\n"
# define ERR_EXIT_XTRARG "minishell: exit: too many arguments\n"
# define ERR_EXIT_NONUMERIC "minishell: exit: %s: numeric argument required\n"
# define ERR_XTRA_ARG "minishell: %s: too many arguments\n"
# define ERR_XPORTID "minishell: export: `%s': not a valid identifier\n"
# define ERR_SYSFUNC "minishell: %s: %s\n"
# define ERR_SYSFUNC_DUP "minishell: %d: %s\n"

#endif