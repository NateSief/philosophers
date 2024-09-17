#include "philosophers.h"

#ifdef pthread_mutex_lock
# undef pthread_mutex_lock  // Correction de la faute de frappe
#endif

#ifdef pthread_mutex_unlock
# undef pthread_mutex_unlock  // Correction de la faute de frappe
#endif

int 	my_lock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);  // Cela appelle la vraie fonction pthread_mutex_lock
	printf("%s [LOCK] --- %s in function %s at line %d%s\n", RED,  mutex_name, func, line, RESET);
	return (ret);
}

int		my_unlock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line)
{
	int	ret;

	ret = pthread_mutex_unlock(mutex);  // Cela appelle la vraie fonction pthread_mutex_unlock
	printf("%s [UNLOCK] --- %s in function %s at line %d%s\n", BLUE, mutex_name, func, line, RESET);
	return (ret);
}
