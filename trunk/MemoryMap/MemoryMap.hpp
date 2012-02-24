/*
 *  @author Shardul Vikram, Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

#ifndef MEMORYMAP_HPP
#define MEMORYMAP_HPP

#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
namespace filemap {
//implement locks

//immap
//ommap
//iommap
class MemoryMap{
private:
	size_t min_file_size;	//= 4096
	char* addr;			//address user point to
	char* pa_addr;			//page address for memory alignment pa_addr <= addr 
	char* MBegin;
	char* MEnd;
	char* MSpace;			//extra space after the last element
	int fd;				//file descriptor
	int oflag;			//= O_RDWR,O_CREAT, O_RDWR etc...
	size_t flength;		//flength = length of the data requested by the user
	size_t fLengthFromOffset;		//fLengthFromOffset = flength + offset - pa_offset
	size_t fsize;			//fsize = file size
	off_t pa_offset,offset;	//page_offset
	struct stat sb;

public:
	~MemoryMap();

	MemoryMap();

	void DoMemoryMap(const char* fname,int fOflag,size_t fLength=0,off_t mOffset=0);
	//mark const and no except to relevant functions so as to optimize the code

	int    MResize(size_t new_size);//new_size is the size of the file and not the mmapped area
	
	void*  begin() const{return MemoryMap::MBegin;}

	void*  end() const{return MemoryMap::MEnd;}
	//int    current(){return addr - begin;}
	size_t size() const {return MemoryMap::fsize;}
	
	size_t length() const{return MemoryMap::flength;}

	void*  MRead() const{return MemoryMap::addr;}

	void*  MWrite(off_t position, void* data,size_t num);

	bool   MInsert(off_t position, void* data, size_t num);

	bool   MFlush() {return msync(MemoryMap::addr, MemoryMap::fLengthFromOffset, MS_SYNC) == 0;} 

};
}
#endif // MEMORYMAP_HPP
