#	ifndef INIT_UTILC_H
#	define INIT_UTILC_H

#include "struct.h"

int		allocate_memory(t_data *data);
int		init_mutex(t_data *data);
int		init_value(t_data *data, char **argv);

#	endif
