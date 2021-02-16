//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

    Instruction() { };
    ~Instruction() { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?
    enum InstructionType {
        ST_MachineLanguage, 	    // A machine language instruction.
        ST_AssemblerInstr,  		 // Assembler Language instruction.
        ST_Comment,          		   // Comment or blank line
        ST_End                   		// end instruction.
    };

    // Parse the Instruction.
    InstructionType ParseInstruction(string a_line);

    // Translates the Instruction
    pair<int, string>TranslateInstruction(string& a_temp, int a_loc);

    // clear values like opcode, operand 
    void clearValues();

    // sets first Operand
    string setOperand1(string m_Operand);

    // sets second Operand
    string setOperand2(string m_Operand);

    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc);

    // To access the label
    inline string& GetLabel()
    {
        return m_Label;
    };
    // To determine if a label is blank.
    inline bool isLabel()
    {
        return !m_Label.empty();
    };

private:


    // The elemements of a instruction
    string m_Label;         // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand;      // Generic operand when there are two operand
    string m_Operand1;     // The first operand
    string m_Operand2;     // The second operand

    string m_instruction;    // The original instruction.

    InstructionType m_type; // The type of instruction.

    // Pads a string to a_size by adding 0s in the beginning
    string pad(string& a_temp, int a_size);

    // Check for and return the opcode of the given string. 
    int OpcodeLocation(string& a_temp);

    // converts the string to a lower case value
    string lowercase(string& a_temp);

    // For storing parsed instructions
    vector<string> m_parsedInstruction;

};

