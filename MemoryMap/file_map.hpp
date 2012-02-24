/*
 *  This header file defines the interfaces for the file_map libray 
 *  @author Shardul Vikram, Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

#ifndef FILEMAP_HPP
#define FILEMAP_HPP

#include "MemoryMap.hpp"
namespace filemap
{

	enum mode { RD = O_RDONLY, WR = O_WRONLY, RW = O_RDWR};
	using namespace std;
	template<typename T>
	class file_map : public MemoryMap
	{
		T* fptr;
		T* first;
		T* last;
		const char* file_name;
		size_t file_size;
		size_t num_elements;
		size_t offset; // in terms of number of elements from the start
		
	public:
		file_map(const char *fname, int mode, size_t size = 0,off_t f=0);

		// Method to map the files and return pointer of a specified type
		void map(const char *fname, int mode, size_t len = 0, off_t f=0);

		file_map(const file_map<T>& fil):MemoryMap() //copy constructor
		{
		
		  DoMemoryMap(fil.file_name,O_RDWR,0,0);

      file_map::fptr = (T*)MemoryMap::MRead();
      file_map::first = (T*)MemoryMap::begin();

      file_map::num_elements = MemoryMap::length()/sizeof(T);
      file_map::last = first + num_elements -1;
      file_map::file_size = MemoryMap::size();
		}


    file_map& operator= (file_map& fil) //assignment operator overload, copies one mapping to another
    {
    //file_name = fil.file_name;

			if(file_name == fil.file_name)
				return *this;
      file_size = fil.file_size;
      MemoryMap::MResize(file_size);
      fptr = (T*)MemoryMap::MRead();
      first = (T*)MemoryMap::begin();
      last = (T*)MemoryMap::end();
      //mode = fil.mode;
      //map(file_name, mode, file_size);
      //fptr = (T*)addr;
      T* itr = fil.first;
      while(itr <= fil.last){
        *fptr = *itr;
        fptr++;
        itr++;
      }
    return *this;
    }

    void mapfrom(T* arr, int l); // map the array values to the file

    size_t resize( size_t final_size); // resize the file mapping to this size

		void update_file();

		size_t get_size();
		
		T* begin(){return first;}

		T* end(){return last;}

		void write_data (off_t position, T* data);

		T const& operator[] (int i) const ;
		T& operator[] (int i);

		~file_map()
    { }
	};

} //namespace filemap

//ugly templates
#include "file_map.cpp"

#endif // FILEMAP_HPP
