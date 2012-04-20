#ifndef MUTEX_HPP
#define MUTEX_HPP

template<typename T>
class Mutex{
  public:
    Mutex();
    ~Mutex();
    void Acquire();
    void Release();
  private:
    T* mutex;
};
#endif //MUTEX_HPP
