#pragma once

class MemoryBlock{
	public:
		int position;
		int length;
}

class Memory{
	private:
		int available_memory;
	public:
		MemoryBlock* get_block(int length);
};