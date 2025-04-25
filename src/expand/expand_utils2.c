/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:38:08 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/24 21:22:05 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * we_have_value - Appends a variable's value to the current expansion result.
 *
 * @value: The value to append.
 * @temp: Temporary string used during concatenation.
 * @expan: Pointer to the current expanded result string.
 *
 * Joins `*expan` with `value`, frees both, and updates `*expan`.
 * Returns 0 on success or -1 on allocation failure.
 */
static int we_have_value(char *value, char *temp, char **expan)
{
	temp = ft_strjoin(*expan, value);
	free(value);
	if (!temp)
	{
		ft_putendl_fd("malloc failed", 2);
		return (-1);
	}
	free(*expan);
	*expan = temp;
	return (0);
}

/**
 * get_value - Retrieves the value of an environment variable.
 *
 * @env: Linked list of environment variables.
 * @name: Name of the variable to search for.
 *
 * Returns a newly allocated copy of the value,
 * an empty string if not found, or (char *)-1 on failure.
 */
char *get_value(t_env *env, char *name)
{
	t_env *temp = env;
	char *value;

	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			value = ft_strdup(temp->value);
			if (!value)
			{
				ft_putendl_fd("malloc fail", 2);
				return ((char *)-1);
			}
			return (value);
		}
		temp = temp->next;
	}
	value = ft_strdup("");
	if (!value)
	{
		ft_putendl_fd("malloc fail", 2);
		return ((char *)-1);
	}
	return (value);
}

/**
 * handle_value - Resolves and appends a variable's value to the result string.
 *
 * @msh: Pointer to the shell structure (for environment and exit code).
 * @data: Pointer to the t_vdata structure with variable info.
 *
 * Expands normal variables or special cases like `$?`.
 * Returns 0 on success, 1 on failure.
 */
int handle_value(t_msh *msh, t_vdata *data)
{
	if (data->name[0] == '?')
	{
		data->value = ft_itoa(msh->exit_code);
		if (!data->value)
			return (1);
		if (we_have_value(data->value, data->temp, data->expan) == -1)
			return (1);
		return (0);
	}
	data->value = get_value(msh->envl, data->name);
	if (data->value == (char *)-1)
		return (1);
	if (we_have_value(data->value, data->temp, data->expan) == -1)
		return (1);
	return (0);
}



/**
 * ft_strjoin_char - Appends a single character to a string.
 *
 * @str: Input string to append to.
 * @c: The character to add.
 *
 * Returns a new string containing `str` followed by `c`,
 * or NULL on allocation failure.
 */
char *ft_strjoin_char(char *str, char c)
{
	size_t	len = str ? ft_strlen(str) : 0;//TODO: can we even use this?
	char	*new_str = malloc(len + 2);
	size_t	i = 0;

	if (!new_str)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

/**
 * tildes_home - Expands the '~' symbol to the user's home directory.
 *
 * @msh: Pointer to the shell structure for accessing environment variables.
 * @str: The original input string.
 * @expan: Pointer to the string being expanded.
 * @arg: Pointer to the expansion context.
 *
 * Concatenates `~` and appends `$HOME` to the result string.
 * Returns the updated index or -1 on failure.
 */
int tildes_home(t_msh *msh, char *str, char **expan, t_expand *arg)
{
	char *temp, *temp2, *value;

	temp2 = ft_strndup(&str[arg->start], arg->i - arg->start);
	temp = ft_strjoin(*expan, temp2);
	free(temp2);
	free(*expan);
	*expan = temp;
	arg->i++;

	value = get_value(msh->envl, "HOME");
	if (value)
	{
		temp = ft_strjoin(*expan, value);
		if (!temp)
		{
			free(value);
			return (-1);
		}
		free(*expan);
		*expan = temp;
		free(value);
	}
	return (arg->i);
}
