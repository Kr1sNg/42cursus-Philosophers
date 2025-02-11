#include "dining.h"

/* spinlock to synchronize philos start */

void wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;

}


/* monitor busy waits until all threads are running */

bool	all_threads_running()
{
	
}

