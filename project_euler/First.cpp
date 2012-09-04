#include<iostream>
using namespace std;

int main()
{
  int limit = 1000;
  int sum3 =0;
  for(int i = 0;i<=limit/3;i++)
  {
    sum3 += i*3;
  }
  
  int sum5 =0;
  for(int i = 0;i<limit/5;i++)
  {
    sum5 += i*5;
  }

  int sum15 =0;
  for(int i = 0;i<=limit/15;i++)
  {
    sum15 += i*15;
  }
cout<<"Sum3 = "<<sum3<<"\n";
cout<<"Sum5 = "<<sum5<<"\n";
cout<<"Sum = "<<sum3+sum5-sum15<<"\n";
return 0;

}

