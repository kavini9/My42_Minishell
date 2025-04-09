/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:38 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 15:04:17 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_free_int_arr_with_size - Frees an array of integer pointers
 *                             with a known size.
 *
 * @array: Pointer to the array of integer pointers to be freed.
 * @size: The number of elements in the array.
 */
void	ft_free_int_arr_with_size(int **array, int size)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * error - Prints an error message and updates the shell's exit code.
 *
 * @msh: Pointer to the shell structure to update the exit code.
 * @str: Error message to be displayed.
 */
void	error(t_msh *msh, char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	msh->exit_code = 1;
}

/**
 * clean_env - Frees a linked list representing
 *             the shell's environment variables and an optional array.
 *
 * @ll: Pointer to the head of the environment linked list.
 * @array: Optional array of strings to free (e.g., msh->envl).
 */
void	clean_env(t_env *ll, char **array)
{
	t_env	*temp;

	if (array)
		ft_free_array(array);
	while (ll)
	{
		temp = ll;
		free(ll->name);
		free(ll->value);
		ll = ll->next;
		free(temp);
	}
}

/**
 * clean_redir - Frees a linked list of redirection nodes.
 *
 * @head: Pointer to the head of the redirection list.
 */
void	clean_redir(t_redir *head)
{
	t_redir	*temp;

	while (head)
	{
		temp = head;
		free(head->file);
		free(head->delimiter);
		free(head->heredoc_name);
		head = head->next;
		free(temp);
	}
}
