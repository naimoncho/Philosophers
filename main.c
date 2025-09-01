#include "philo.h"

int	main(int argc, char **argv)
{
	t_table table;

	if (!parse_arguments(argc, argv, &table))
		return (EXIT_FAILURE);
	if (!init_simulation(&table))
		return (EXIT_FAILURE);
	start_simulation(&table);
	cleanup_simulation(&table);
	return (EXIT_SUCCESS);
}