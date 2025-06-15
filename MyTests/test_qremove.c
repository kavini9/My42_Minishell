#include <stdio.h>
# include "lib/libft/libft.h"
# include <readline/readline.h>

char *remove_quotes(char *q_arg)
{
  int sq;
  int dq;
  int len;
  char *arg;

  sq = 0;
  dq = 0;
  len = ft_strlen(q_arg);
  arg = q_arg;
  while(len--)
  {
    if (*q_arg == '\'' && !dq)
    {
        sq = !sq;
        ft_memmove(q_arg, q_arg + 1, len + 1);
    }
    else if (*q_arg == '"' && !sq)
    {
        dq = !dq;
        ft_memmove(q_arg, q_arg + 1, len + 1);
    }
    else
        q_arg++;  
  }
  return(arg);
}


int main(void)
{
    char *line;

    while(1)
    {
        line = readline(">");
        if (!ft_strcmp(line, "exit"))
			break;
        printf("arg = %s\n", remove_quotes(line));
    }
}