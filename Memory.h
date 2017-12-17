#pragma once

#include <cstdlib>

class MemoryBlock{
	public:
		MemoryBlock(int position, int length);
		int position;
		int length;
};

class Memory{
	private:
		int available_memory;
	public:
		Memory(int memory_size);
		MemoryBlock* get_block(int length);
};