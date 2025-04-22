#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * Print details of the redirection list in a command.
 */
void print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("    Redirection Type: %d\n", redir->type);
		printf("    File: %s\n", redir->file ? redir->file : "NULL");
		printf("    Delimiter: %s\n", redir->delimiter ? redir->delimiter : "NULL");
		printf("    Heredoc Name: %s\n", redir->heredoc_name ? redir->heredoc_name : "NULL");
		printf("    Expand: %s\n", redir->expand ? "true" : "false");
		redir = redir->next;
	}
}

/**
 * Print all parsed commands inside the msh struct.
 */
void print_parsed_commands(t_msh *msh)
{
	if (!msh || !msh->cmds)
	{
		printf("No commands parsed.\n");
		return;
	}
printf("_line: %d\n", __LINE__);
	for (int i = 0; i < msh->cmd_count && msh->cmds[i]; i++)
	{
		t_cmd *cmd = msh->cmds[i];
		printf("Command #%d:\n", i + 1);
		printf("  Raw Segment: %s\n", cmd->seg ? cmd->seg : "NULL");
		printf("  Command: %s\n", cmd->command ? cmd->command : "NULL");
printf("_line: %d\n", __LINE__);

		printf("  Arguments:\n");
printf("_line: %d\n", __LINE__);
		if (cmd->cmd)
		{
			for (int j = 0; cmd->cmd[j]; j++)
				printf("    [%d]: %s\n", j, cmd->cmd[j]);
		}
		else
		{
			printf("    NULL\n");
		}
printf("_line: %d\n", __LINE__);
		if (cmd->redir_start)
		{
			printf("  Redirections:\n");
			print_redirections(cmd->redir_start);
		}

		printf("  Input FD: %d, Output FD: %d\n", cmd->input_fd, cmd->output_fd);
		printf("\n");
	}
}


/**
 * Print parsing error message.
 */
void handle_parse_error(t_msh *msh)
{
	fprintf(stderr, "Invalid command. Exit Code: %d\n", msh->exit_code);
}

/**
 * Initialize msh struct with safe defaults.
 */
static void msh_init(t_msh *msh, char **envp)
{
	(void)envp;
	ft_memset(msh, 0, sizeof(t_msh));

	msh->cwd = getcwd(NULL, 0);
	if (!msh->cwd)
	{
		perror("getcwd failed");
		exit(EXIT_FAILURE);
	}

	msh->old_wd = ft_strdup(msh->cwd);
	if (!msh->old_wd)
	{
		perror("ft_strdup failed for old_wd");
		free(msh->cwd);
		exit(EXIT_FAILURE);
	}

	msh->cmds = NULL; // Will be set in build_command_structs
}

/**
 * Main entry point for Minishell parser test.
 */
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_msh msh;
	char *line;

	msh_init(&msh, envp);

	while (1)
	{
		line = readline("minishell> ");

		if (!line)
		{
			printf("\nExiting minishell...\n");
			break;
		}

		if (*line)
		{
			add_history(line);

			if (msh_parse(line, &msh))
				handle_parse_error(&msh);
			else
			{
				printf("Valid command!\n");
				print_parsed_commands(&msh);
			}

			if (msh.cmds)
			{
				clean_cmds(msh.cmds);  // <- already frees each t_cmd and msh.cmds itself
				msh.cmds = NULL;       // <- avoid dangling pointer
			}
		}
	}

	free(msh.cwd);
	free(msh.old_wd);

	return 0;
}
