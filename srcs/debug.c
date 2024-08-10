#include "philosophers.h"

#ifdef pthread_mutex_lock
# undef pthread_mutex_lock
#endif

#ifdef pthread_mutex_unlock
# undef pthread_mutex_unlock
#endif

int my_pthread_mutex_lock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line) {
    int ret = pthread_mutex_lock(mutex);  // Call the real pthread_mutex_lock
    if (ret == 0) {
        printf("[LOCK] Mutex '%s' locked in function %s at line %d\n", mutex_name, func, line);
    } else {
        printf("[ERROR] Failed to lock mutex '%s' in function %s at line %d: %s\n", mutex_name, func, line, strerror(ret));
    }
    return ret;
}

int my_pthread_mutex_unlock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line) {
	int ret = pthread_mutex_unlock(mutex);  // Call the real pthread_mutex_unlock
    if (ret == 0) {
        printf("[UNLOCK] Mutex '%s' unlocked in function %s at line %d\n", mutex_name, func, line);
    } else {
        printf("[ERROR] Failed to unlock mutex '%s' in function %s at line %d: %s\n", mutex_name, func, line, strerror(ret));
    }
    return ret;
}
