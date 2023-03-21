#include <sys/semaphore.h>

#include "philosopher_semaphores.h"

void	unlink_all_semaphores(void)
{
	sem_unlink(EXECUTION_SEMAPHORE);
	sem_unlink(FORKS_SEMAPHORE);
	sem_unlink(PHILOSOPHER_DIED_SEMAPHORE);
}
