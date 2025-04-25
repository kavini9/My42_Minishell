/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:07:27 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/15 19:47:06 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* handle_new_expand - Appends a newly expanded variable value to the result.
*
* @temp: Temporary string containing the value to append.
* @expan: Pointer to the string accumulating the expanded result.
*
* Concatenates `temp` to `*expan`, freeing both originals.
* Returns 0 on success, -1 on memory allocation failure.
*/
static int handle_new_expand(char *temp, char **expan)
{
   char *new_expanded;

   new_expanded = ft_strjoin(*expan, temp);
   if (!new_expanded)
   {
       ft_putendl_fd("malloc failed", 2);
       return (-1);
   }
   free(temp);
   free(*expan);
   *expan = new_expanded;
   return (0);
}

/**
* init_vdata - Initializes a t_vdata structure for variable expansion.
*
* @data: Pointer to the t_vdata structure to initialize.
* @expan: Pointer to the result string accumulating expanded content.
* @temp: Temporary variable storage used in expansion.
* @name: Variable name being expanded.
*/
static void init_vdata(t_vdata *data, char **expan, char *temp, char *name)
{
   data->value = NULL;
   data->expan = expan;
   data->temp = temp;
   data->name = name;
}

/**
* finalize_expand - Finalizes the expansion process for a variable.
*
* @msh: Pointer to the shell structure with env state.
* @data: Pointer to variable expansion data.
* @arg: Pointer to the expansion context (used to track position).
*
* Appends the variable value, duplicates its name, and updates the start index.
* Returns 0 on success, or 1 on error.
*/
static int finalize_expand(t_msh *msh, t_vdata *data, t_expand *arg)
{
   if (handle_value(msh, data))
       return (1);
   arg->name = ft_strdup(data->name);
   if (!arg->name)
       return (1);
   arg->start += ft_strlen(arg->name) + 1;
   free(arg->name);
   return (0);
}

/**
* oh_a_dollar - Expands a variable following a dollar sign ('$').
*
* @msh: Pointer to the shell structure for environment access.
* @str: Input string being expanded.
* @expan: Pointer to the string building the expanded result.
* @arg: Pointer to the t_expand context.
*
* Supports normal vars ($HOME), special vars ($?), and handles result appending.
* Returns updated index on success, or -1 on failure.
*/
int oh_a_dollar(t_msh *msh, char *str, char **expan, t_expand *arg)
{
   char	name[100];
   char	*temp;
   int		indx = 0;
   t_vdata	data;

   temp = ft_strndup(&str[arg->start], arg->i - arg->start);
   if (!temp || handle_new_expand(temp, expan))
   {
       if (temp)
           free(temp);
       return (-1);
   }
   arg->i++;
   if (str[arg->i] == '?')
       just_a_quest(str, name, &indx, arg);
   else
       we_need_name(arg, str, name, &indx);
   init_vdata(&data, expan, temp, name);
   if (finalize_expand(msh, &data, arg))
       return (-1);
   return (arg->start);
}

/**
* we_have_dollar - Expands a variable in the current segment (e.g., $VAR).
*
* @msh: Pointer to the shell structure for env access.
* @arg: Pointer to the expansion context.
* @str: Input string to expand.
*
* Expands the variable at the current index (`arg->i`), appends its value
* to `arg->value`, and updates position tracking. Cleans up temporary data.
*
* Return: 0 on success, -1 on failure.
*/
int we_have_dollar(t_msh *msh, t_expand *arg, char *str)
{
   char	*temp;
   char	*new_res;
   //int		s_exp = arg->i;

   temp = ft_strdup("");
   if (!temp)
       return (-1);
   arg->start = arg->i;
   arg->i = oh_a_dollar(msh, str, &temp, arg);
   if (arg->i == -1)
   {
       free(temp);
       return (-1);
   }
   new_res = ft_strjoin(arg->value, temp);
   if (!new_res)
   {
       free(temp);
       return (-1);
   }
   free(arg->value);
   free(temp);
   arg->value = new_res;
   return (0);
}
