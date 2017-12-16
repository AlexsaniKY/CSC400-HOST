#include "Memory.h"

using namespace std;

MemoryBlock::MemoryBlock(int position, int length){


}

MemoryBlock* Memory::get_block(int length){
	if(length<=available_memory){
		MemoryBlock* m = new MemoryBlock(0, length);
		return m;
	}

}