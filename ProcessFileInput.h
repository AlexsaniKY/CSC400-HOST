#pragma once

#include "pcb.h"
#include <string>

using namespace std;

class ProcessFileInput{
	private:
		FILE * inputliststream;
	public:
		ProcessFileInput();
		~ProcessFileInput();
		bool open(string filename);
		bool hasNext();
		PcbPtr next();
};