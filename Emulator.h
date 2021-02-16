//
//		Emulator class - supports the emulation of VC1620 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H
#include "Errors.h"
class emulator {

public:

    const static int MEMSZ = 100000;	// The size of the memory of the VC1620.

    emulator() {
        memset(m_memory, 0, MEMSZ * sizeof(int));
    }
    // Records instructions and data into VC1620 memory.
    bool insertMemory(int a_location, long long a_contents);
   
    // Runs the VC1620 program recorded in memory.
    bool runProgram( );

private:

    long long int m_memory[MEMSZ];  // Memory for VC1620
    bool isEnd;          // flag for termination
    long long int accumulator[1000];    // The accumulator for the VC1620
};

#endif

