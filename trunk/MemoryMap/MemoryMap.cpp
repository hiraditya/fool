#include "MemoryMap.hpp"
#include <stdio.h>
//madvise(map_ptr,len,MADV_SEQUENTIAL);
namespace filemap {

bool MAPPING_FAILED = false;
bool FILE_NOT_OPENED = false;
bool FSTAT_ERROR = false;
bool READING_FILE_OF_SIZE_ZERO = false;
bool OFFSET_PAST_END = false;
bool FTRUNCATE_FAILED = false;
bool MUNMAP_FAILED = false;
bool MUNMAP_MSYNCH_FAILED = false;
bool RESIZE_FAILED = false;
 
// Copy constructor
MemoryMap::MemoryMap()
  :fd(-1),fLengthFromOffset(0),addr(0),pa_offset(0)
{ }

void MemoryMap::DoMemoryMap(const char* fname,int fOflag,size_t fLength,off_t mOffset)
{
	min_file_size = sysconf(_SC_PAGE_SIZE);
	flength = (fLength > 0) ? fLength : 0;
    offset  = (mOffset > 0) ? mOffset : 0;
    oflag   = fOflag;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd      = (oflag == O_RDONLY) ? open(fname,oflag) : open(fname,oflag|O_CREAT,mode);
	//in write mode (if the file doesn't exist)the file is created with min_file_size
	if(fd == -1) {
		FILE_NOT_OPENED = true;
		return;
	}								//EXIT_FAILURE
	if (fstat(fd, &sb) == -1){							/* To obtain file size */
     	FSTAT_ERROR = true;
     	close(fd);
     	return;
    }								//EXIT_FAILURE
     
    size_t initial_file_size = sb.st_size;

    if(initial_file_size == 0){
     	if(oflag == O_RDONLY){
     		READING_FILE_OF_SIZE_ZERO = true;
     		return;
     	}						//EXIT_FAILURE
     	
     	flength = min_file_size;
     	
     	if(ftruncate(fd, flength) == -1){
    			FTRUNCATE_FAILED = true;
    			return;
		}	//if O_RDWR change the file size

		if (fstat(fd, &sb) == -1){							/* To obtain file size */
	     	FSTAT_ERROR = true;
	     	close(fd);
	     	return;
	    }								//EXIT_FAILURE
        initial_file_size = sb.st_size;

		fLengthFromOffset = flength;		//ignore the offset value fLengthFromOffset >= flength
		
    }
    else{
	    if (offset >= initial_file_size) {
			OFFSET_PAST_END = true;
			return;
	    }								//EXIT_FAILURE
	    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);//to load in multiple of pages
			
		if(flength == 0 || flength+offset>initial_file_size){
			if((offset == 0) && (oflag != O_RDONLY) ){
				if(ftruncate(fd, flength) == -1){
    					FTRUNCATE_FAILED = true;
    					return;
    				}
				if (fstat(fd, &sb) == -1){							/* To obtain file size */
		     		FSTAT_ERROR = true;
		     		close(fd);
		     		return;
		     	}								//EXIT_FAILURE
	          	initial_file_size = sb.st_size;
   				  				
			}	//if WRITE MODE change the file size

     	//if no preference about the length to be displayed, display the whole file
     		else {
     			flength = initial_file_size - offset;
     			fLengthFromOffset = flength + offset - pa_offset;
     		}
     	}
     	
     	fLengthFromOffset = flength + offset - pa_offset;
    }
    int MFlags = (oflag == O_RDONLY) ? PROT_READ : PROT_READ|PROT_WRITE;//checking the mode of opening the file
    pa_addr = static_cast<char*>(mmap(NULL, fLengthFromOffset,MFlags, MAP_SHARED, fd, pa_offset));

    if (pa_addr == MAP_FAILED){
     	close(fd);
     	fsize = 0;
     	MAPPING_FAILED = true;
     	return;
    }
    else{
     	addr = pa_addr + offset - pa_offset;
     	fsize = initial_file_size;
     	MBegin = addr;
     	MEnd = addr + flength -1;
    }
 

}

MemoryMap::~MemoryMap() 
{ 
    munmap(pa_addr,fLengthFromOffset);
    if (flength != fLengthFromOffset){
        ftruncate(fd, fLengthFromOffset);   
    }
    close(fd);
    //shm_unlink(file_name);
}

int MemoryMap::MResize(size_t new_size) 
{
	if(oflag == O_RDONLY) 
		return -1;
// 	if (new_size <= flength){return flength;} to be implemented
//throw warning that if size decreases it may truncate the file contents

    	if(munmap(pa_addr, fLengthFromOffset) != 0){
    		if(msync(addr, fLengthFromOffset, MS_SYNC) != 0)
	    		MUNMAP_MSYNCH_FAILED = true;//boom!!!
    		else MUNMAP_FAILED = true;
    		return -1;
    	}
    	
    	if(ftruncate(fd, new_size) == -1){
    		FTRUNCATE_FAILED = true;
    		return -1;
    	}
    	pa_addr = static_cast<char*> (mmap(NULL, new_size,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    	if (pa_addr == MAP_FAILED){
			fLengthFromOffset = 0;
			flength = 0;
			fsize = 0;
			addr = pa_addr;
			MAPPING_FAILED = true;	
    		return -1;
    		
    	}
    	else{
			if (fstat(fd, &sb) == -1){							/* To obtain file size */
				FSTAT_ERROR = true;
				return -1;
			}
			addr = pa_addr;								//EXIT_FAILURE
			fsize = sb.st_size;
			flength = new_size;    
    		fLengthFromOffset = flength;
    		pa_offset = 0;
    		MBegin = addr;
    		MEnd = addr + flength -1;
    	}
return flength;
}

void* MemoryMap::MWrite(off_t position, void* data,size_t num)
{
	if(position < 0 || position > flength) 
		return NULL;
	size_t n = (num < flength) ? num : flength - position;
		return memcpy(MBegin + position,data,n);
}

bool MemoryMap::MInsert(off_t position, void* data, size_t num)
{
	size_t old_flength = flength;
	size_t new_flength = flength + num;
	if(new_flength == MResize(new_flength)){
		memmove(MBegin+position+num,MBegin+position,old_flength-position+1);
		MWrite(position,data,num);
		return true;
	}

	else 
		return false;
}
} // namespace filemap
