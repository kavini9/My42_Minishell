#include "../../includes/minishell.h"

void reset_cmd_attr(t_msh *msh)
{
    if (msh -> cmd)
        free_cmd(msh -> cmd);
    msh -> cmd = NULL;
    msh -> cmd_count = 0;
    close_all_hdocfd(msh -> hdocfd_l);//may be in init memset hdocfdl to -1.
}