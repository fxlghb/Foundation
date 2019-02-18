#ifndef __MUTEX_H__
#define __MUTEX_H__
#include "base.h"

enum{
    MUTEX_CLASS_DEFAULT,
    MUTEX_CLASS_REF,
    MUTEX_CLASS_READ,
};

//��װ�ٽ���
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

//��װ�ٽ����Ľ�����˳�
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
