#include "posix_sys.h"

using namespace ndb;

Mutex::Mutex() {
  assert(!::pthread_mutex_init(&_mutex, NULL));
}

Mutex::~Mutex() {
  assert(!::pthread_mutex_destroy(&_mutex));  
}

bool Mutex::lock() {
  return ::pthread_mutex_lock(&_mutex) == 0;
}

bool Mutex::trylock() {
  return ::pthread_mutex_trylock(&_mutex) == 0;
}

bool Mutex::unlock() {
  return ::pthread_mutex_unlock(&_mutex) == 0;
}

Cond::~Cond() {
  assert(!::pthread_cond_destroy(&_cond));
}

Cond::Cond(Mutex &mutex):_mutex(mutex) {
  assert(!::pthread_cond_init(&_cond, NULL));
}

bool Cond::wait() {
  return ::pthread_cond_wait(&_cond, &_mutex._mutex) == 0;
}

bool Cond::wait(long i) {
  struct timespec ts = {0};
  struct timeval t = now();
  ts.tv_nsec = t.tv_usec*1000 + i*1000000;
  ts.tv_sec = t.tv_sec + ts.tv_nsec/1000000000;
  ts.tv_nsec = ts.tv_nsec%1000000000;
  return ::pthread_cond_timedwait(&_cond, &_mutex._mutex, &ts) == 0;
}

bool Cond::notify() {
  return ::pthread_cond_signal(&_cond) == 0; 
}

RWLock::RWLock() {
  assert(pthread_rwlock_init(&_rwlock, NULL) == 0);
}

RWLock::~RWLock() {
  assert(pthread_rwlock_destroy(&_rwlock) == 0);
}


bool RWLock::rdlock() {
  return pthread_rwlock_rdlock(&_rwlock) == 0;
}

bool RWLock::tryrdlock() {
  return pthread_rwlock_tryrdlock(&_rwlock) == 0;
}

bool RWLock::unlock() {
  return pthread_rwlock_unlock(&_rwlock) == 0;
}

bool RWLock::wrlock() {
  return pthread_rwlock_wrlock(&_rwlock) == 0;
}

bool RWLock::trywrlock() {
  return pthread_rwlock_trywrlock(&_rwlock) == 0;
}

