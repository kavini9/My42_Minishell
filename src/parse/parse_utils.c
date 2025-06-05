/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:02:37 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/03 22:13:29 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	 check_quotes(char *start, char *end)
{
	int	single_quote = 0;
	int	double_quote = 0;

    while (*start && start != end)
	{
		if (*start == '\'' && !double_quote)
			single_quote = !single_quote * (int) *start ; 
		else if (*start == '"' && !single_quote)
			double_quote = !double_quote * (int) *start; 
		start++;
	}
	return (single_quote || double_quote);
}

void skip_whitespaces(char **str)
{
    while (**str && ft_strchr(" \t\n\r\f\v", **str))
        (*str)++;
}

int redir_skip(char *seg)
{
    int skip;

    skip = 0;
    while(*seg && ft_strchr("< \t\n\r\f\v>", *seg))
    {
        skip++;
        seg++;
    }
    return (skip);
}

//auxiliary. delete later

void print_segments(char **seg)
{
    printf("pirnting segments\n");
    while (*seg)
    {
        printf("[%s]\n", *seg);
        seg++;
    }
}

void print_tokens(t_token **token)
{
    t_token *tok_arr;

    while (*token)
    {
        printf("pirnting tokens for each segment\n");
        tok_arr = *token;
        while(tok_arr -> token)
        {
            printf("[%s]        redir: %i\n", tok_arr -> token, (int) tok_arr -> redir );
            tok_arr++;
        }
        token++;
    }
}

void print_expand_arrays(t_token **token)
{
    t_token *tok_arr;
    char **expn;

    while (*token)
    {
        printf("pirnting expn for each segment\n");
        tok_arr = *token;
        while(tok_arr -> token)
        {
            printf("pirnting expn for token: %s\n", tok_arr -> token);
            expn = tok_arr -> expn;
            while(expn && *expn)
            {
                printf("[%s]\n", *expn);
                expn++;
            }
            tok_arr++;
        }
        token++;
    }
}