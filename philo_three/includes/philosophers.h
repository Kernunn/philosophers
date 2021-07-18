#	ifndef PHILOSOPHERS_H
#	define PHILOSOPHERS_H

void *philosophers(void *arg);
void *check_state(void *arg);
void check_number_of_well_fed_philosophers(t_data *data);
void check_philosopher_death(t_data *data);

#	endif
