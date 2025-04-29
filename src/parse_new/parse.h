/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:38:01 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/29 23:48:22 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

typedef struct s_token
{
    char    *token;
    char    *expand;
} t_token;

typedef struct s_parse
{
    char        *seg;
    int			sgl;
	int			dbl;
    t_token     *token;
}   t_parse;

#endif