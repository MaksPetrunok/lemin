// header

#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "hashmap.h"
# include "farm.h"

typedef struct s_inp_lst	t_inp_lst;

struct			s_inp_lst
{
	char		*str;
	t_inp_lst	*next;
};

extern t_farm		g_farm;
extern t_inp_lst	*g_raw_input;

int					read_input(void);


#endif
