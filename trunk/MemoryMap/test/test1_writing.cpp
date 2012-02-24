#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "file_map.hpp"

using namespace std;
using namespace filemap;

int main()
{

int max = 1000;

timespec ts, te;

// Open  a file using fstream for writing

  clock_gettime(CLOCK_MONOTONIC, &ts);

  ofstream myfile;
  myfile.open ("fstream1.txt");
  for(int i = 0; i < max; i++)
	{
  		myfile << i+1;
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

std::cout << "\n Time taken by fstream to carry out " << max << " writes to file in nanoseconds \t"
                        << (temp.tv_nsec) << "\n" << std::endl;


//  cout << "Done" << endl;

// Open a file using filemap for writing

  clock_gettime(CLOCK_MONOTONIC, &ts);

  file_map<int> myfile2("map1.txt", O_RDWR, 1000000);
	for(int i = 0; i < 100000; i++)
        {
                myfile2[i] = i + 1;
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

  std::cout << "\n Time taken by file_map to carry out " << max << " writes to file in nanoseconds \t"
                        << (temp.tv_nsec) << "\n" << std::endl;


}
