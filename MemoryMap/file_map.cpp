/*
 * This header file defines the interfaces for the file_map libray 
 * 
 *
 *
 */
#include "MemoryMap.hpp"
#include "file_map.hpp"

namespace filemap
{

	template <typename T>
	file_map<T>::file_map(const char *fname, int mode, size_t len, off_t f):MemoryMap()
	{
		DoMemoryMap(fname,mode,len*sizeof(T),f*sizeof(T));
	
		file_map::fptr = (T*)MemoryMap::MRead();
		file_map::first = (T*)MemoryMap::begin();

		file_map::num_elements = MemoryMap::length()/sizeof(T);
		file_map::last = first + num_elements -1;
		file_map::file_size = MemoryMap::size();
		
	}

	template <typename T>
	void file_map<T>::map(const char *fname, int mode, size_t len, off_t f)
	{
		DoMemoryMap(fname,mode,len*sizeof(T),f*sizeof(T));
		file_map::fptr = (T*)MemoryMap::MRead();
		file_map::first = (T*)MemoryMap::begin();
		file_map::num_elements = MemoryMap::length()/sizeof(T);
		file_map::last = first + num_elements -1;
		file_map::file_size = MemoryMap::size();
		
	}

	template <typename T>
	void file_map<T>::update_file()
	{	
		MemoryMap::MFlush();
	}

	template <typename T>
	size_t file_map<T>::get_size()
	{
		return MemoryMap::size();
	}

	template <typename T>
	T const& file_map<T>::operator[] (int i) const
	{	 
		return file_map::fptr[i];
	}

	template <typename T>
        T& file_map<T>::operator[] (int i)
        {
		if (i*sizeof(T) > file_size)
			{
			//	std::cout << file_size << "  need = " << i*sizeof(T) << std::endl;
				update_file();
				MemoryMap::MResize(2*file_size);
	                        fptr = (T*)MemoryMap::MRead();
        	                first = (T*)MemoryMap::begin();
                	        last = (T*)MemoryMap::end();
				file_map::file_size = MemoryMap::size();
			}
                return *(file_map::fptr + i);
        }

	
	template <typename T>
	void file_map<T>::write_data (off_t position, T* data)
	{	 
		size_t num = sizeof(data);
		MemoryMap::MWrite(position*sizeof(T), data, num);
	}
};
