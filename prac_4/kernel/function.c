#include "function.h"

void Print(char* str,unsigned int line,unsigned int color){
	char* pointer = (char *)(0xB8000 + 160 * line);
	
	for(;*str != 0; str++){
		*pointer++ = *str;
		*pointer++ = color;
	}
	return;
	
}