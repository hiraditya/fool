#include <iostream>

#include "file_map.cpp"

using namespace std;
using namespace filemap;

int main()
{
 file_map<long> a("abc.dat", RW, 8192,0);

        long* p = a.begin();
        char c[] = "abcdefghijklmnopqrstabcde";
        long i =0;
        int j =0;
        for(i=0;i<100;i++){
                //a.write_data(i,&i);
     //         a[i] = i+100;
        }

        cout<<"i="<<i;
                i=0;
//      a.update_file();

        for(p = a.begin();i < 100;++i,++p){
                cout<<" "<<*p<<" "<< i <<endl;
        }


      cout<<endl<<a.get_size();
}

