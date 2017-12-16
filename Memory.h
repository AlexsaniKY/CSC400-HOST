#pragma once

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
		MemoryBlock* get_block(int length);
};