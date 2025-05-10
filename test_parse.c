#include "includes/minishell.h"
#include "lib/libft/libft.h"
#include <readline/readline.h> //for readline
#include <readline/history.h> 

void msh_init(t_msh *msh);
void	msh_parse(char *line, t_msh *msh);
void print_segments(char **seg);
void init_parse_structs(t_msh *msh, char *line);
void	init_token(t_msh *msh, int cmd_count);
int	count_pipes(char *line);
void line_split_bypipe(t_msh *msh, char *line, char **seg_arr);
int	 check_quotes(char *start, char *curr);

int	 check_quotes(char *start, char *curr)
{
	int	single_quote = 0;
	int	double_quote = 0;

    while (*start && start != curr + 1)
	{
		if (*start == '\'' && !double_quote)
			single_quote = !single_quote; 
		else if (*start == '"' && !single_quote)
			double_quote = !double_quote; 
		start++;
	}
    //printf("single: %i | double: %i\n", single_quote, double_quote);
	return (single_quote || double_quote);
}

void line_split_bypipe(t_msh *msh, char *line, char **seg_arr)
{
    char *start;
    char *seg;
    char *temp;
    
    start = line;
    while (*line)
    {
        //printf("%c", *line);
        if ((*(line + 1) == '|' || !*(line + 1)) && !check_quotes(start, line))//change the check quotes function
        {
            seg = ft_substr(start, 0, line - start + 1);
            temp = seg;
            if (temp)
            {
                seg = ft_strtrim(temp, " \t\n\r\f\v");
                free(temp);
            }
            //printf("split_by_pipe: %s\n", seg);
            if (!seg)
                exit(printf("# minishell: Error:Malloc Fail. %s\n", msh -> cwd ));//TODO: ERROR MALLOC.
            *seg_arr = seg;
            seg_arr++;
            if (*(line + 1)) 
                start = line + 2;
        }
        line++;
    }
}

int	count_pipes(char *line)
{
	int	pipe_count;
	char *start;

	pipe_count = 0;
	start = line;
	while (*line)
	{
		if (*line == '|' && !check_quotes(start, line))
			pipe_count++;
		line++;
	}
	return (pipe_count);
}

void	init_token(t_msh *msh, int cmd_count)
{
	msh -> aux -> token = ft_calloc(cmd_count + 1, sizeof(t_token **));
	if (!msh -> aux -> token)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC. Free aux -> seg.
	while (cmd_count--)
	{
		*(msh -> aux -> token) = ft_calloc(1, sizeof(t_token *));
		if (!*(msh -> aux -> token))
			exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC. Since we calloced we can free until we find it NULL.
		(msh -> aux -> token)++;
	}
}

void init_parse_structs(t_msh *msh, char *line) 
{
	msh -> cmd_count = count_pipes(line) + 1;
	msh -> aux -> seg = ft_calloc(msh -> cmd_count + 1, sizeof(char *));
	if (!msh -> aux -> seg)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
	init_token(msh, msh -> cmd_count);
}

void print_segments(char **seg)
{
    while (*seg)
    {
        printf("<%s>\n", *seg);
        seg++;
    }
}

void	msh_parse(char *line, t_msh *msh)
{
	t_parse	aux;//in static memory remember to assign to cmd struct before leaving this function.

	msh -> aux = &aux;
	init_parse_structs(msh, line);
	line_split_bypipe(msh, line, msh -> aux -> seg);
    print_segments(msh -> aux -> seg);
	//seg_tokenize(msh);
}

void msh_init(t_msh *msh)
{
	ft_memset(msh, 0, sizeof(t_msh)); //DES: sets everything to NULL
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		exit(printf("minishell: cd: error retrieving current directory: getcwd: %s\n", msh -> cwd));
	msh -> old_wd = ft_strdup(msh -> cwd);//if we go one level up the old pwd is different
	if (!msh -> old_wd)
		exit(printf("minishell: fatal error: memory allocation failed in %s.\n", msh -> cwd));
	//duplicate_env(msh, envp);
	//set_shlvl(msh, msh -> envl);
}

int main(void)
{
	t_msh	msh;
	char *line;

	msh_init(&msh);
    line = readline("minishell> ");
    msh_parse(line , &msh);
    return (1);
}