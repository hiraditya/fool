/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

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
