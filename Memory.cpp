#include "Memory.h"

using namespace std;



MemoryBlock* Memory::get_block(int length){
	if(length<=available_memory){
		MemoryBlock m = MemoryBlock();
		return &m;
	}

}