#ifndef __MUTEX_H__
#define __MUTEX_H__
#include "base.h"

enum{
    MUTEX_CLASS_DEFAULT,
    MUTEX_CLASS_REF,
    MUTEX_CLASS_READ,
};

//封装临界区
class mutexLock{
public:
    mutexLock(int type=MUTEX_CLASS_DEFAULT);
    ~mutexLock();
    int lock();
    int trylock();
    int unlock();
private:
    pthread_mutex_t m_mutex;
    pthread_mutexattr_t m_mutexAttr;
};

//封装临界区的进入和退出
class Guard{
public:
    Guard(mutexLock& mutex):m_mutex(mutex){
        m_mutex.lock();
    }
    ~Guard(){
        m_mutex.unlock();
    }
private:
    mutexLock &m_mutex;
};

#endif
