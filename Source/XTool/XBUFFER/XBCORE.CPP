#include "xglobal.h"

void XBuffer::alloc(unsigned int sz)
{
	buf = (char*)malloc(size = sz);
	offset = 0L;
	radix = XB_DEFRADIX;
	digits = XB_DEFDIGITS;
	MakeFree = 1;
	if(size) *buf = 0;
}

XBuffer::XBuffer(void* p,int sz)
{
	buf = (char*)p;
	size = sz;
	offset = 0;
	radix = XB_DEFRADIX;
	digits = XB_DEFDIGITS;
	MakeFree = 0;
	automatic_realloc = 0;
}

void XBuffer::free(void)
{
	if(MakeFree && buf){
		::free(buf);
		buf = NULL;
		}
}

void XBuffer::fill(char fc)
{ memset(buf,fc,size); }

void XBuffer::set(int off,int mode)
{
	switch(mode){
		case XB_BEG:
			offset = off;
			break;
		case XB_CUR:
			offset+=off;
			break;
		case XB_END:
			offset = size - off;
			break;
		}
}

unsigned int XBuffer::read(void* s, unsigned int len) 
{	
	memcpy(s, buf + offset, len); 
	offset += len; 
	return len; 
}

void XBuffer::handleOutOfSize()
{
	if(automatic_realloc)
		buf = (char*)realloc(buf, size *= 2);
	else {
		xassert(0 && "Out of XBuffer");
		ErrH.Abort("Out of XBuffer");
	}
}

unsigned int XBuffer::write(const void* s, unsigned int len, int bin_flag) 
{	
	while(offset + len >= size) 
		handleOutOfSize();

	memcpy(buf + offset, s, len);
	offset += len;

	if(!bin_flag)
		buf[offset] = '\0';

	return len;
}

XBuffer& XBuffer::operator< (const char* v) 
{ 
	if(v) 
		write(v, strlen(v), 0); 
	return *this; 
}

XBuffer& XBuffer::operator> (char* v) 
{ 
	if(v) 
		read(v, strlen(buf + offset) + 1); 
	return *this; 
}

