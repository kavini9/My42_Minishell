//auxiliary. delete later
#include "../includes/minishell.h"

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
            printf("token: %s\n", tok_arr -> token);
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

void print_cmd_members(t_cmd **cmd)
{
    char **cmd_arr;
    t_redir **redir_arr;
    int i;

    while (*cmd)
    {
        printf("printing cmd_memebers for each cmd segment\n");
        cmd_arr = (*cmd) -> cmd;
        i = 0;
        while (cmd_arr && *cmd_arr)
        {
            printf("cmd %i: [%s]\n", i++, *cmd_arr);
            cmd_arr++;
        }
        redir_arr = (*cmd) -> redir;
        i = 0;
        while (redir_arr && *redir_arr)
        {
            printf("redir %i:   type: %i    flag: %i    [%s]\n", i++, (*redir_arr) -> type, (*redir_arr) -> ambi_o_hdexp, (*redir_arr) -> fname_o_del);
            redir_arr++;
        }
        cmd++;
    }
}