#include "includes/minishell.h"
#include "lib/libft/libft.h"
#include <readline/readline.h> //for readline
#include <readline/history.h> 

void	*ft_realloc(void *ptr, size_t size_prev, size_t size_new)
{
	void	*ptr_new;

	if (!ptr)
		return (malloc(size_new));
	if (!size_new)
	{
		free(ptr);
		return (NULL);
	}
	ptr_new = malloc(size_new);
	if (!ptr_new)
		return (NULL);//shouldn't we free ptr?
	if (size_prev > 0)
	{
		if (size_prev > size_new)
			ft_memcpy(ptr_new, ptr, size_new);
		else
			ft_memcpy(ptr_new, ptr, size_prev);
	}
	free(ptr);
	return (ptr_new);
}

void skip_whitespaces(char **str)
{
    while (**str && ft_strchr(" \t\n\r\f\v", **str))
        (*str)++;
}

int set_redir_type(t_token *token, char *seg)
{
    if (*seg == '<' && *(seg + 1) == '<')
        token -> redir = REDIR_HDOC;
    else if (*seg == '>' && *(seg + 1) == '>')
        token -> redir = REDIR_APPEN;
    else if (*seg == '<')
        token -> redir = REDIR_INP;
    else if (*seg == '>')
        token -> redir = REDIR_OUTP;
    else
        return (0);
    return (1);
}

int get_token_len(char *seg, t_token *token, int tok_len)
{
    int redir_flg;
    int quote_flg;
    int is_white;

    redir_flg = 0;
    quote_flg = 0;
    while (*seg)
    {
        is_white = (ft_strchr(" \t\n\r\f\v", *seg) != NULL);
        if ((*seg == '\'' || *seg == '"') && !quote_flg)
            quote_flg = (int) *seg;
        else if ((*seg == '\'' || *seg == '"') && quote_flg == (int) *seg)
            quote_flg = 0;
        if (redir_flg && !is_white && !(*seg == '<' || *seg == '>'))
            redir_flg = 0;
        else if ((*seg == '<' || *seg == '>') && !quote_flg && !redir_flg && tok_len)
            break;
        else if ((*seg == '<' || *seg == '>') && !quote_flg && !redir_flg)
            redir_flg = set_redir_type(token, seg);
        if (is_white && !quote_flg && !redir_flg)
            break;
        tok_len++;
        seg++;
    }
    return (tok_len);
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

void extract_token(t_msh *msh, t_token **token, char *seg)
{
    int     tok_len;
    int     arr_len;
    int     size;

    arr_len = 0;
    size = sizeof(t_token);
    while (*seg)
    {
        *token = ft_realloc(*token, arr_len * size, (arr_len + 1) * size);
        if (!token)
            exit(printf("Malloc Error token array\n"));
        ft_memset(&(*token)[arr_len], 0, size);
        tok_len = get_token_len(seg, &(*token)[arr_len], 0);
        (*token)[arr_len].token = ft_substr(seg, redir_skip(seg), tok_len - redir_skip(seg));
        if (!(*token)[arr_len].token)
            exit(printf("Malloc Error token %i\n", arr_len));
        seg += tok_len;
        skip_whitespaces(&seg);
        arr_len++;
    }
    *token = ft_realloc(*token, arr_len * size, (arr_len + 1) * size);
    if (!*token)
        exit(printf("Malloc Error token array\n"));
    ft_memset(&(*token)[arr_len], 0, sizeof(t_token));
}

void	seg_tokenize(t_msh *msh, t_parse *aux)
{
	char    **seg;
    t_token **token;
    
    seg = aux -> seg;
    token = aux -> token;
    while (*seg)
    {
        extract_token(msh, token, *seg);
        seg++;
        token++;
    } 
}

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

void line_split_bypipe(t_msh *msh, char *line, char **seg_arr)
{
    char *start;
    char *seg;
    char *temp;
    
    start = line;
    while (*line)
    {
        if ((*(line + 1) == '|' || !*(line + 1)) && !check_quotes(start, line + 1))//change the check quotes function
        {
            seg = ft_substr(start, 0, line - start + 1);
            temp = seg;
            if (temp)
            {
                seg = ft_strtrim(temp, " \t\n\r\f\v");
                free(temp);
            }
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
		if (*line == '|' && !check_quotes(start, line + 1))
			pipe_count++;
		line++;
	}
	return (pipe_count);
}

void init_parse_structs(t_msh *msh, char *line) 
{
	msh -> cmd_count = count_pipes(line) + 1;
	msh -> aux -> seg = ft_calloc(msh -> cmd_count + 1, sizeof(char *));
	if (!msh -> aux -> seg)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC
    msh -> aux -> token = ft_calloc(msh -> cmd_count + 1, sizeof(t_token *));
	if (!msh -> aux -> token)
		exit(printf("# minishell: Error:Malloc Fail.\n"));//TODO: ERROR MALLOC. Free aux -> seg.
}

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

void	msh_parse(char *line, t_msh *msh)
{
	t_parse	aux;//in static memory remember to assign to cmd struct before leaving this function.

	msh -> aux = &aux;
	init_parse_structs(msh, line);
	line_split_bypipe(msh, line, msh -> aux -> seg);
    print_segments(msh -> aux -> seg);
	seg_tokenize(msh, msh -> aux);
    print_tokens(msh -> aux -> token);
    //init_cmd_struct(msh, msh -> cmd_count);
    expand_and_setup_cmd(msh, msh -> aux -> token);
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