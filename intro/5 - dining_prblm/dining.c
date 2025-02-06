#include "dining.h"

int	main(int ac, char **av)
{
	t_table table;

	if (ac == 5 || ac == 6)
	{
		// 1. check
		parse_input(&table, av);
		// 2. creating the actual thing
		data_init(&table);
		// 3. dinner
		dinner_start(&table);
		// 4. check leaks -> when all reach the limit dinners or one died
		clean(&table);
	}
	else
		error_exit("Wrong input!\n"
			G "Usage: ./philo int int int int [int]\n" RST);
		

}