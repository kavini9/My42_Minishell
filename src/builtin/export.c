/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:26:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/29 02:43:36 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static int is_valid_id(char *x_var)
{
    if (!*x_var || !(ft_isalpha(*x_var) || *x_var == '_'))
        return (0);
    while(*x_var && *x_var != '=')
    {
        if (!ft_isalnum(*x_var) && *x_var != '_')
            return (0);
        x_var++;
    }
    return (1);
}

static void	format_print_x_var(char *x_var)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(x_var, '=');
	if (eq)
	{
		key = ft_substr(x_var, 0, eq - x_var);
		if (!key)
			printf("format print c_var key error\n");
		if (ft_strcmp(key, "_"))
			printf("declare -x %s=\"%s\"\n", key, eq + 1);
		free(key);
	}
	else
		printf("declare -x %s\n", x_var);	
}

static void    display_x_var(char **envl, char *floor)
{
    char    **lex_min;
    char    **iter;
    int	len;
    
    iter = envl;
    len = 0;
    while (iter[len])
        len++;
    while(len--)
    {
        lex_min = envl;
        iter = envl;
        while(*lex_min && !(ft_strcmp(*lex_min, floor) > 0))
            lex_min++;
        while (*iter)
        {
            if(ft_strcmp(*lex_min, *iter) > 0 && ft_strcmp(*iter, floor) > 0 )
                lex_min = iter;
            iter++;
        }
        format_print_x_var(*lex_min);
        floor = *lex_min;
    }  
}

void    builtin_export(t_msh *msh, char **cmd)
{
    if (!*(++cmd))
        return (display_x_var(msh -> envl, ""));
    while (*cmd)
    {
        if(!is_valid_id(*cmd))
            printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", *cmd);//TODO:Errpr
        else
            set_env(msh, msh -> envl, *cmd);
        cmd++;
    }
}
