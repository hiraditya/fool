#include<iostream>
using namespace std;

int main()
{
  int fib = 1, i1=0, i2=1;

  double sum=0;

  int limit = 4000000;
  
  do {
    fib = i1 + i2;
    i1 = i2;
    i2 = fib;
    cout<<"ith fib number: "<<fib<<"\n";
    if(fib%2 == 0){
      sum += fib;
      cout<<"Even:"<<fib<<"Sum = "<<sum<<"\n";
    }
  }while(fib<limit);

  cout<<"Sum ="<<sum<<"\n";

  return 0;
} 
