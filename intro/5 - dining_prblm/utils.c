#include "dining.h"
#include <stdlib.h>

void	error_exit(const char *error)
{
	printf(R "🚩 %s 🚩\n" RST, error);
	exit(EXIT_FAILURE);
}

/* get time */
long gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday failed!");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong imput!");
	return (42);
}

/* precise usleep, the real one suck */
void	precise_usleep(long usec, t_table *table)
{
	long	start = gettime(MICROSECOND);
	long	elapsed;
	long	rem;

	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		// to get a spinlock threshold
		if (rem > 1e3)
			usleep(rem / 2);
		else
			//spinlock
		{	
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

