#include <iostream>
#include <string>
#include <fstream>
#include <file_map.cpp>
#include <time.h>

using namespace std;
using namespace filemap;

int main()
{

const int max = 1000;

timespec ts, te;

// Open  a file using fstream for writing

  clock_gettime(CLOCK_MONOTONIC, &ts);

  ifstream myfile;
  myfile.open ("fstream1.txt");
  int a[max];	
  for(int i = 0; i < max; i++)
	{
  		myfile >> a[i];
	}
  myfile.close();

  clock_gettime(CLOCK_MONOTONIC, &te);

  timespec temp;
	if ((te.tv_nsec - ts.tv_nsec)<0) {
		temp.tv_sec = te.tv_sec - ts.tv_sec-1;
		temp.tv_nsec = 1000000000+te.tv_nsec-ts.tv_nsec;
	} else {
		temp.tv_sec = te.tv_sec-ts.tv_sec;
		temp.tv_nsec = te.tv_nsec-ts.tv_nsec;
	}
	
	// now time difference is in temp

std::cout << "\n Time taken by fstream to carry out " << max << " reads from file in nanoseconds \t"
                        << (temp.tv_nsec) << "\n" << std::endl;


//  cout << "Done" << endl;

// Open a file using filemap for writing

  clock_gettime(CLOCK_MONOTONIC, &ts);
  int b[max];	
  file_map<int> myfile2("map1.txt", O_RDWR);
	for(int i = 0; i < max; i++)
        {
                b[i] = myfile2[i];
        }
 myfile2.update_file();

  clock_gettime(CLOCK_MONOTONIC, &te);

 // timespec temp;
        if ((te.tv_nsec - ts.tv_nsec)<0) {
                temp.tv_sec = te.tv_sec - ts.tv_sec-1;
                temp.tv_nsec = 1000000000+te.tv_nsec-ts.tv_nsec;
        } else {
                temp.tv_sec = te.tv_sec-ts.tv_sec;
                temp.tv_nsec = te.tv_nsec-ts.tv_nsec;
        }

        // now time difference is in temp

  std::cout << "\n Time taken by file_map to carry out " << max << " reads from file in nanoseconds \t"
                        << (temp.tv_nsec) << "\n" << std::endl;


}
