
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "mutex.h"

//static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
#define TS_LOCK(mutex)   pthread_cleanup_push( (void(*)(void*))pthread_mutex_unlock, (void*)mutex);pthread_mutex_lock(mutex)
#define TS_UNLOCK(mutex) pthread_cleanup_pop(1)



mutexLock::mutexLock(int type)
{
    int ret;

    switch(type)
    {
        case MUTEX_CLASS_DEFAULT:
            ret = pthread_mutex_init(&m_mutex, NULL);
            if(ret < 0)
            {
                printf("pthread_mutex_init fail ret[%d] error[%s]\n",ret,strerror(errno));
            }
            break;
        case MUTEX_CLASS_REF:
            ret = pthread_mutexattr_init(&m_mutexAttr);
            if(ret < 0)
            {
                printf("pthread_mutexattr_init fail ret[%d] error[%s]\n",ret,strerror(errno));
            }
            ret = pthread_mutexattr_settype(&m_mutexAttr, PTHREAD_MUTEX_RECURSIVE_NP);
            if(ret < 0)
            {
                printf("pthread_mutexattr_settype fail ret[%d] error[%s]\n",ret,strerror(errno));
            }
            ret = pthread_mutex_init(&m_mutex, &m_mutexAttr);
            if(ret < 0)
            {
                printf("pthread_mutex_init fail ret[%d] error[%s]\n",ret,strerror(errno));
            }
            break;
        default:
            ret = pthread_mutex_init(&m_mutex, NULL);
            if(ret < 0)
            {
                printf("pthread_mutex_init fail ret[%d] error[%s]\n",ret,strerror(errno));
            }
            break;
    }
}

mutexLock::~mutexLock()
{
    pthread_mutex_destroy(&m_mutex);
}

int mutexLock::lock()
{
    return pthread_mutex_lock(&m_mutex);
}

int mutexLock::trylock()
{
    return pthread_mutex_trylock(&m_mutex);
}

int mutexLock::unlock()
{
    return pthread_mutex_unlock(&m_mutex);
}





