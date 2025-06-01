/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:57:24 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/31 21:05:54 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int is_numeric(char *str)
{
    int digi_count;

    digi_count = 0;
    while ((*str >= 9 && *str <= 13) || *str == ' ' )
		str++;
    if (*str == '-' || *str == '+')
		str++;
    while (*str >= '0' && *str <= '9')
    {
        str++;
        digi_count++;
    }
    while ((*str >= 9 && *str <= 13) || *str == ' ' )
		str++;
    if (*str && !ft_isdigit(*str))
        digi_count = 0;
    return(digi_count);
}

void    builtin_exit(t_msh *msh, char **cmd)
{
    int digi_count;
    long int num;

    digi_count = 0;
    num = 0;
    if (msh -> cmd_count == 1)
        ft_putendl_fd("exit", STDERR_FILENO);
    if(++cmd)
        digi_count = is_numeric(*cmd);
    if (digi_count)
        num = ft_atol(*cmd);
    if ((*cmd && !digi_count) || (digi_count >= 19 && (num == 0 || num == -1)))
        msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 2, ERR_EXIT_NONUMERIC, *cmd);
    else if (*(cmd + 2))
        return(msh_error(msh, (LOG) << 8 | 1, ERR_EXIT_XTRARG, NULL));//see if clean is required here
    else
        msh -> exit_code = (uint8_t) num;
    msh_clean(msh);
    exit(msh -> exit_code);
}

/*
$ bash
$ echo $SHLVL
3
$ exit 1234567891012345678901212
exit
bash: exit: 1234567891012345678901212: numeric argument required
$ echo $?
2
$ echo $SHLVL
2
$
2
*/


/*
$ bash
$ echo $SHLVL
3
$ exit 12 34
exit
bash: exit: too many arguments
$ echo $?
1
$ echo $SHLVL
3
*/


/*
$ bash
$ echo $SHLVL
3
$ exit 255 rt
exit
bash: exit: too many arguments
$ echo $?
1
$ echo $SHLVL
3
*/

/*
$ echo $SHLVL
3
$ exit qwwfw
exit
bash: exit: qwwfw: numeric argument required
$ echo $?
2
$ echo $SHLVL
2
*/


/*
$ bash
$ echo $SHLVL
3
$ exit a b
exit
bash: exit: a: numeric argument required
$ echo $?
2
$ echo $SHLVL
2
*/


/*
$ bash
$ echo $SHLVL
3
$ exit -1
exit
$ echo $?
255
$ echo $SHLVL
2
*/


/*
$ bash
$ echo $SHLVL
3
$ exit 256
exit
$ echo $?
0
$ echo $SHLVL
2
*/