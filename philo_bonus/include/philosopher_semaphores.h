#ifndef PHILOSOPHER_SEMAPHORES_H
# define PHILOSOPHER_SEMAPHORES_H

# define FORKS_SEMAPHORE "forks"
# define EXECUTION_SEMAPHORE "execution_semaphore"
# define PHILOSOPHER_DIED_SEMAPHORE "philosopher_died"
# define SHOULD_KILL_ALL_PHILOSOPHERS_SEMAPHORE "should_kill_all_philosophers"

void	unlink_all_semaphores(void);

#endif //PHILOSOPHER_SEMAPHORES_H
