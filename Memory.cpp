#include "Memory.h"

using namespace std;

MemoryBlock::MemoryBlock(int pos, int len){
	position = pos;
	length = len;

}

Memory::Memory(int memory_size){
	available_memory = memory_size;
}

MemoryBlock* Memory::get_block(int length){
	if(length<=available_memory){
		MemoryBlock* m = new MemoryBlock(0, length);
		return m;
	}
	else return (MemoryBlock*)NULL;
}