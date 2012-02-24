#include <iostream>

#include "file_map.cpp"

using namespace std;
using namespace filemap;

int main()
{
 file_map<int> a("new.dat", O_RDWR);

	//int* p;
	int i = 0, j = 1;
	for(i;i < 10;i++){
	a[i] = ++j;
	}

//	a[0] = 10;
//	a[5] = 20;
	
	a.update_file();

// Check for assignment

	file_map<int> b("a.dat", O_RDWR);
	b = a;

	cout << "Here here \n" << endl;
	
	for(i=0; i < 10; i++){
	cout<<"value at " << i << "th position = " << b[i] << endl;
	}

	cout << "Starting and ending addresses are:" << endl;
	cout << b.begin() << endl;
	cout << b.end() << endl;


// Copy constructor

	cout << "Here here copy constructor 1" << endl;

	file_map<int> c(a);

        cout << "Here here copy constructor" << endl;
        
        for(i=0; i < 10; i++){
        cout<<"value at " << i << "th position = " << c[i] << endl;
        }

        cout << "Starting and ending addresses are:" << endl;
        cout << c.begin() << endl;
        cout << c.end() << endl;

	
	
	cout<< " file size = " << c.get_size() << endl;

}

