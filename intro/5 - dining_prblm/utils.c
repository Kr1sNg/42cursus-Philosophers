#include "dining.h"
#include <stdlib.h>

void	error_exit(const char *error)
{
	printf(R "🚩 %s 🚩\n" RST, error);
	exit(EXIT_FAILURE);
}