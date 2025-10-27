#include "function.h"
#include "interupt.h"
void main(){
	char str[24] = "Hello Kernel in C haha";
	char lines[24] = "====================";
	Print(lines,4,0x08);
	Print("Hello Kernel in C haha",5,0x09);
	Print(lines,6,0x08);
	init_interupt(); // register IDT
	int line = 5;
	while(1){
	}
	
	return;
}

