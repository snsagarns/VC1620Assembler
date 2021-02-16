#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"


/**/
/*
bool emulator::insertMemory(int a_location, long long a_contents)

NAME

	emulator::insertMemory(int a_location, long long a_contents)) - Inserts the contents into the memory location

SYNOPSIS

	bool emulator::insertMemory(int a_location, long long a_contents)
	a_location		-->			location of the machine language
	a_contents		-->			the machine language content 12 digits

DESCRIPTION

	This function inserts the contents into VC 1620 Computer

RETURNS

	Returns true if successfully inserted in memory, false otherwise.

AUTHOR

	Sagar Neupane

DATE

	02:15 AM 12/24/2020

*/
/**/
bool emulator::insertMemory(int a_location, long long a_contents)
{
	if (a_location >= 0 && a_location < MEMSZ) {
		m_memory[a_location] = a_contents;
		return true;
	}
	else {
		Errors::RecordError("Location out of bound");
		return false;
	}
} /* bool emulator::insertMemory(int a_location, long long a_contents) */


/**/
/*
bool emulator::runProgram()

NAME

	emulator:: runProgram() - // Runs the VC1620 program recorded in memory.

SYNOPSIS

	bool emulator::runProgram()

DESCRIPTION

	This function runs the emulator for VC 1620 Computer

RETURNS

	Returns true if the program executed successfully. Otherwise, return false 

AUTHOR

	Sagar Neupane

DATE

	02:15 AM 12/24/2020

*/
/**/
bool emulator::runProgram()
{
	int iloc = 100;
	string UserInput;
	char sign = 'n';

	while(true){
		// extracting opcode from machine code
		long long contents = m_memory[iloc];
		int OpCode = contents / 10000000000;

		// extracting first address
		int temp = contents % 10000000000;
		int address1 = temp / 100000;

		// extracting second address
		int address2 = temp % 100000;

		// cout << OpCode  << endl;
		// cout << address1 << endl;
		// cout << address2 << endl;
		

		switch (OpCode)
		{

		case 1:
			// ADD
			accumulator[address1] += m_memory[address2];
			iloc++;
			break;

		case 2:
			// SUBTRACT
			accumulator[address1] -= m_memory[address2];
			iloc++;
			break;

		case 3:
			// MULTIPLY
			accumulator[address1] *= m_memory[address2];
			iloc++;
			break;

		case 4:
			// DIVIDE
			accumulator[address1] /= m_memory[address2];
			iloc++;
			break;

		case 5:
			// COPY
			m_memory[address1] = m_memory[address2];
			iloc++;
			break;

		case 7:
			// READ
			cout << "?";
			cin >> UserInput;
			if (UserInput[0] == '-' || UserInput[0] == '-') {
				sign = UserInput[0];
				UserInput = UserInput.erase(0, 1);
			}
			for (int i = 0; i < UserInput.size(); i++) {
				if (!isdigit(UserInput[i])) {
					cout << "Each character of Input must be digit" << endl;
				}
			}
			m_memory[address2] = stoi(UserInput);
			if (sign == '-') {
				m_memory[address2] *= -1;
			}

			iloc++;
			break;

		case 8:
			// WRITE
			cout << m_memory[address2] << endl;
			iloc++;
			break;

		case 9:
			// B :  goes to the provided address for next instruction
			iloc = address2;
			break;

		case 10:
			// BM goes to the address if content of accumulator is less than 0

			if (accumulator[address1] < 0) {
				iloc = address2;
			}
			else {
				iloc++;
			}
			break;

		case 11:
			// BZ
			if (accumulator[address1] == 0) {
				iloc = address2;
			}
			else {
				iloc++;
			}
			break;

		case 12:
			// BP
			if (accumulator[address1] > 0) {
				iloc = address2;
			}
			else {
				iloc++;
			}
			break;

		case 13:
			// HALT
			exit(1);
			break;
		default:
			cerr << "Illegal Opcode" << endl;
			return false;
		}
		if (isEnd) {
			return true;
		}
	}
	return false;
}
/* bool emulator::runProgram() */


					





























		