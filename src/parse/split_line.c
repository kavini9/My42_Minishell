/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:56 by aoshinth          #+#    #+#             */
/*   Updated: 2025/03/24 14:43:23 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 *
 * @seg: The input string to trim.
 *
 * Finds the first and last non-whitespace characters in the string, shifts the
 * relevant portion to the start of the buffer, and null-terminates the result.
 * Modifies the input string in-place. Returns the trimmed string.
 */
char *trim_whitespace(char *seg)
{
    int     end;
    int     start;
    int     len;

    if (!seg)
        return (NULL);
    start = 0;
    end = ft_strlen(seg) - 1;
    while (seg[start] && ft_isspace(seg[start]))
        start++;
    while (end >= start && ft_isspace(seg[end]))
        end--;
    len = end - start + 1;
    ft_memmove(seg, seg + start, len + 1);
    seg[len] = '\0';
    return (seg);
}

/**
 * segment_handler - Processes and trims a segment of the input string.
 *
 * @token: Pointer to the token structure where the segment will be stored.
 * @line: The input string containing the segment.
 * @start: Start index of the segment in the input string.
 * @end: End index of the segment in the input string.
 *
 * Extracts a substring from the input string between indices `start` and `end`, trims
 * any leading or trailing whitespace, and assigns it to the `token_name` field of the
 * token structure. Handles memory allocation errors and returns 1 on failure,
 * 0 on success.
 */
static int segment_handler(t_token *token, char *line, int start, int end)
{
    char    *trimmed;

    trimmed = ft_strndup(line + start, end - start);
    if (!trimmed)
    {
        ft_putendl_fd("Failed to allocate memory for trimmed string", 2);
        return (1);
    }
    trimmed = trim_whitespace(trimmed);
    token->token_name = trimmed;
    if (!token->token_name)
    {
        ft_putendl_fd("No token name in struct", 2);
        free(trimmed);
        return (1);
    }
    return (0);
}

/**
 * split_line - Splits the input string by
 * 			   unquoted pipe ('|') characters.
 *
 * @line: The input string to parse and split.
 * @msh: Pointer to the shell structure containing command information.
 *
 * Iterates through the input string, identifying pipe-separated segments while
 * respecting quotes. Calls `segment_handler` for each segment to trim whitespace
 * and assign it to the corresponding token structure. Updates the `tokens` array
 * in `msh` with these segments. Returns 0 on success, or 1 on failure.
 */
int split_line(char *line, t_msh *msh)
{
    int     i;
    int     start;
    int     index;

    i = 0;
    start = 0;
    index = 0;
    while (line[i])
    {
        if (line[i] == '|' && !check_quotes(line, i))
        {
            if (segment_handler(msh->tokens[index], line, start, i))
                return (1);
            start = i + 1;
            index++;
        }
        i++;
    }
    if (segment_handler(msh->tokens[index], line, start, i))
        return (1);
    index++;
    return (0);
}

