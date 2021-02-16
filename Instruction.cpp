#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"
#include "SymTab.h"

/**/
/*
Instruction::InstructionType Instruction:: ParseInstruction(string a_line)

NAME

    Instruction::ParseInstruction - parse the incoming instruction.

SYNOPSIS

    Instruction::InstructionType Instruction:: ParseInstruction(string a_line)
    a_line    --> line from the source code that is to be parsed

DESCRIPTION

    This function parses the given line into opcode, operand and label and returns the type of instruction. Errors are not checked here

RETURNS
   
   returns the type of machine instruction of enum type Instruction::InstructionType

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
Instruction::InstructionType Instruction:: ParseInstruction(string a_line)
{
    // Initializes each element of instructions to empty string
    clearValues();

    m_instruction = a_line;
    m_parsedInstruction.clear();
    m_parsedInstruction.resize(0);

    // Finds the place where a comment starts in a line 
    size_t iSemicolon = a_line.find(';');

    // Get rid of the comment from a line
    if (iSemicolon != string::npos){
        m_instruction = a_line.erase(iSemicolon);
    }

    stringstream ss(m_instruction);
    string parse_inst;

    // successively parse each string in a line and pass it into vector
    while (ss >> parse_inst) {
        m_parsedInstruction.push_back(parse_inst);
    }

    // Indicating type of instructions using enum type feature
    // Empty Line or Line with comment
    if (m_parsedInstruction.empty())
        m_type = InstructionType(2);     // ST_Comment (Comment or blank line)

       // Origin Location ORG
    else if (lowercase(m_parsedInstruction[0]) == "org")
        m_type = InstructionType(1);    // Assembler Language Instruction

     // Instruction to end the assembly language program
    else if (lowercase(m_parsedInstruction[0]) == "end")
        m_type = InstructionType(3);    // ST_End (End instruction)

    // Instruction to end the machine code execution
    else if (lowercase(m_parsedInstruction[0]) == "halt")
        m_type = InstructionType(0);    // A Machine Language Instruction

    else if (lowercase(m_parsedInstruction[0]) == "bp")
        m_type = InstructionType(0);    // A Machine Language Instruction

    // If the instruction has only opcode and operand
    else if (m_parsedInstruction.size() == 2)
        m_type = InstructionType(0);  // A Machine Language Instruction

    else{
        m_Label = m_parsedInstruction[0];

        // Determining the type of other parsed instruction
        if (lowercase(m_parsedInstruction[1]) == "dc" || lowercase(m_parsedInstruction[1]) == "ds")
            m_type = InstructionType(1);   // Assembler Language Instruction

        else
            m_type = InstructionType(0);   // A Machine Language Instruction
    }

    return m_type;
}/* Instruction::InstructionType Instruction:: ParseInstruction(string a_line) */


/**/
/*
pair<int, string> Instruction::TranslateInstruction(string& a_temp, int a_loc)

NAME

    Instruction::TranslateInstruction(string& a_temp, int a_loc)

SYNOPSIS

    pair<int, string> Instruction::TranslateInstruction(string& a_temp, int a_loc)
    a_temp      ---> Instruction Line that is to be parsed and translated to machine code
    a_loc       ---> Location of the Instruction for translated machine code of VC1620

DESCRIPTION

    This function translates the instructions in the source code to the equivalent machine code of VC1620
    and also deals with errors if there are any while parsing and translating

RETURNS

    returns a pair of location of machine code and corresponding machine code for emulator program after
    being formatted in the form of VC 1620 Computer's machine code

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
pair<int, string> Instruction::TranslateInstruction(string& a_temp, int a_loc)
{
    // Parse the line and get instruction type
    Instruction::InstructionType inst = ParseInstruction(a_temp);

    // If the instruction has more than four words, it should be an error
    if (m_parsedInstruction.size() > 4) 
        Errors::RecordError("Location " + to_string(a_loc) + " : More than four fields");

    // check if label has more than  10 character
    if (m_Label.length() > 10)
        Errors::RecordError("Location " + to_string(a_loc) + " : More than 10 characters ");
    

    // InstructionType(0) returns machine code equivalent
    if (inst == InstructionType(0)) {
        string assem_code = ""; // For storing the assembly language code for given instruction
        int loc = 0;   // For storing the location
        string temp1 =  "";
        string temp2 = "";
        int loc2 = 0;

        switch (m_parsedInstruction.size()) {
        case(1):
            m_OpCode = lowercase(m_parsedInstruction[0]);
            // Check to see if the word has an opcode in our assembly language
            if (OpcodeLocation(m_OpCode) != -1) {
                string b = "0";
                if (m_OpCode == "halt")
                    assem_code = "13" + pad(b, 10);
                // Halt is the only OpCode which goes without an operand. If it's not halt, it will be error
                else {
                    Errors::RecordError("Location : " + to_string(a_loc) + " : Missing operand");
                    assem_code = to_string(OpcodeLocation(m_OpCode)) + "????????";
                    pad(assem_code, 8);
                }
            }
            // Otherwise report an error
            else {
                Errors::RecordError("Location: " + to_string(a_loc) + " Invalid Operation Command");
                assem_code = "?????";
            }
            break;
        case(2):
            m_OpCode = m_parsedInstruction[0];
            m_Operand1 = m_parsedInstruction[1];

            if (OpcodeLocation(m_OpCode) != -1) {
                assem_code = to_string(OpcodeLocation(m_OpCode));
                pad(assem_code, 2);

                if (SymbolTable::LookupSymbol(m_Operand1, loc)) {
                    string a = to_string(loc);
                    string b = "0";
                    assem_code = assem_code + pad(a, 5) + pad(b, 5);
                }
                else {
                    Errors::RecordError("Location: " + to_string(a_loc) + "Undefined Operand");
                    assem_code = assem_code + m_Operand1;
                }
            }
            else {
                Errors::RecordError("location: " + to_string(a_loc) + " Invalid Operation Command");
                assem_code = "???";
            }
            break;
        case(3):
            // check if the instruction line has label. 
            if (!isLabel()){
                m_OpCode = m_parsedInstruction[0];
                m_Label = m_parsedInstruction[1];
                m_Label = setOperand1(m_Label);
                m_Operand1 = m_Label;
                m_Operand2 = m_parsedInstruction[2];
            }
            else {
                m_Label = m_parsedInstruction[0];
                m_OpCode = m_parsedInstruction[1];
                m_Operand1 = m_parsedInstruction[2];
                m_Operand2 = setOperand2(m_Operand1);
                m_Operand1 = setOperand1(m_Operand1);
            }
            
            if (OpcodeLocation(m_OpCode) != -1) {
                assem_code = to_string(OpcodeLocation(m_OpCode));
                pad(assem_code, 2);

                if (SymbolTable::LookupSymbol(m_Operand1, loc)) {
                    string b = to_string(loc);
                    assem_code = assem_code + pad(b, 5);
                   
                    if (SymbolTable::LookupSymbol(m_Operand2, loc)) {
                        string c = to_string(loc);
                        assem_code = assem_code + pad(c, 5);
                    }
                    else {
                        string d = "0";
                        assem_code = assem_code + pad(d,5);
                    }
                }
                else {
                    Errors::RecordError("Location: " + to_string(a_loc) + " Undefined Operand/Label");
                    assem_code = assem_code + m_Operand1;
                }
            }
            else {
                Errors::RecordError("Location: " + to_string(a_loc) + " Invalid Operation Command");
                assem_code = "?????";
            }
            break;

        default:
            assem_code = "??????";
            break;
        }
        cout << setw(14) << left << a_loc << setw(17) << left << assem_code << a_temp << endl;
        return pair<int, string>(a_loc, assem_code);
    }
    
     if (inst == InstructionType(1) && m_parsedInstruction.size() >= 3 && lowercase(m_parsedInstruction[1]) == "dc") 
            cout << setw(14) << left << a_loc << setw(14) << left << pad(m_parsedInstruction[2], 12) << a_temp << endl;
        
     // Asembler instruction is InstructionType(1)
     else if (inst == InstructionType(1))
            cout << setw(14) << left << a_loc << setw(14) << left << "" << a_temp << endl;
        
     else 
         cout << setw(30) << " " << a_temp << endl;
      
      // End Statement
      if (inst == InstructionType(3))
            return pair < int, string>(0, "end");

       return pair <int, string>(0, "n/a");
}/* pair<int, string> Instruction::TranslateInstruction(string& a_temp, int a_loc) */
    

/**/
/*
int Instruction:: OpcodeLocation(string &a_loc)

NAME

    Instruction::OpcodeLocation(string &a_loc) - Get Opcode for operation

SYNOPSIS

    int Instruction:: OpcodeLocation(string &a_loc);
    a_loc    ----> the variable to get the position/ location of opCode

DESCRIPTION

    This function stores the opcode in map and returns the opocode location

RETURNS

    an integer between 1 and 13 based on the opcode position
    -1 if the opcode does not exist

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
int Instruction:: OpcodeLocation(string &a_loc)
{

   // Storing the Opcodes and Assembly Language Instruction in Map
    map<string, int> opcode_map
    {
        {"add", 1}, {"sub", 2}, {"mult", 3}, {"div", 4},
        {"copy", 5}, {"read", 7}, {"write", 8}, {"b", 9},
        {"bm", 10}, {"bz", 11}, {"bp", 12}, {"halt", 13}
    };

    if (opcode_map[a_loc] <= 13 && opcode_map[a_loc] >= 1)
        return opcode_map[a_loc];

    return -1;
} /* int Instruction:: OpcodeLocation(string &a_loc) */


/**/
/*
string Instruction::setOperand1(string m_Operand)

NAME

    Instruction::setOperand2(string m_Operand) - Checks for comma in the string and return substring

SYNOPSIS

    string Instruction::setOperand1(string m_Operand);
    m_Operand      ---> Combination of Operands with comma

DESCRIPTION

    This function checks for the comma in instruction and extracts the firsst operand eliminating comma character from the string

RETURNS

    substring of string - First Operand

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
string Instruction::setOperand1(string m_Operand) 
{
    string temp;
    size_t icomma = m_Operand.find(',');
    if (icomma != string::npos) {
        temp = m_Operand.substr(0, icomma);
        return temp;
    }
    else {
        return m_Operand;
    }
} /* string Instruction::setOperand1(string m_Operand) */


/**/
/*
string Instruction::setOperand2(string m_Operand)

NAME

    Instruction::setOperand2(string m_Operand) - Eliminates comma and distinguishes second operand

SYNOPSIS

    string Instruction::setOperand2(string m_Operand);
    m_Operand      ---> Combination of Operands with comma

DESCRIPTION

    This function extracts the second operand eliminating comma character from the string

RETURNS

    substring of string - Second Operand

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
string Instruction::setOperand2(string m_Operand)
{
    string temp;
    size_t icomma = m_Operand.find(',');
    if (icomma != string::npos)
        temp = m_Operand.substr(icomma + 1);

    return temp;
}/* string Instruction::setOperand2(string m_Operand) */


/**/
/*
int Instruction::LocationNextInstruction(int a_loc) 

NAME

    Instruction::LocationNextInstruction(int a_loc) - locates the next line of instruction

SYNOPSIS

    int Instruction::LocationNextInstruction(int a_loc);
    a_loc          ---> Location of current instruction for VC1620

DESCRIPTION

    This function computes the location of next line of instruction (machine code) based on the current instruction

RETURNS

    Location for Next Instruction

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
int Instruction::LocationNextInstruction(int a_loc) 
{
    // We don't want to increment location for blank line, comment or end instruction
    if (m_type == InstructionType(2) || m_type == InstructionType(3))
        return a_loc;

    // Checks if the statement is origin statement
    else if (m_type == InstructionType(1)) {
        stringstream ss(m_instruction);
        string a1, a2, a3;
        ss >> a1 >> a2 >> a3;

        // returns the origin location converting string into integer
        if (lowercase(a1) == "org")
            return stoi(a2);

        // for define storage in our source code a and b 
        else if (lowercase(a2) == "ds" )
            return a_loc + stoi(a3);
    }

    // increment location by 1
    return a_loc + 1;
}/* int Instruction::LocationNextInstruction(int a_loc)  */


/**/
/*
string Instruction::lowercase(string& a_temp)

NAME

    Instruction::lowercase(string& a_temp) - changes each letter of the word to lowecase

SYNOPSIS

    string Instruction::lowercase(string& a_temp);
    a_temp          ---> string that this to be changed to lowercase letter

DESCRIPTION

    This function lowercases every letter of string (word) and returns the lowercased string

RETURNS

    lowercased string.

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
string Instruction::lowercase(string& a_temp)
{
    for (int i = 0; i < a_temp.size(); i++)
    {
        a_temp[i] = tolower(a_temp[i]);
    }
    return a_temp;
}/* string Instruction::lowercase(string& a_temp) */


/**/
/*
string Instruction::pad(string& a_temp, int a_size)

NAME

    Instruction::pad(string& a_temp, int a_size) - Formats the string

SYNOPSIS

    string Instruction::pad(string& a_temp, int a_size);
    a_temp          ---> string that is supposesd to be formatted
    a_size          ---> the size to which the string is to be formatted

DESCRIPTION

    This function formats the string by adding a string "0" at the beginning until the given size of string is formed

RETURNS

    formatted string after reshaping into the mentioned size.

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
string Instruction::pad(string& a_temp, int a_size)
{
    if (a_temp.size() == a_size)
        return a_temp;

    else
    {
        for (int i = a_temp.size(); i < a_size; i++)
            a_temp.insert(0, "0");
    }
    return a_temp;
}/* string Instruction::pad(string& a_temp, int a_size) */


/**/
/*
void Instruction::clearValues()

NAME

    void Instruction::clearValues() - Clears all the values of the class variables

SYNOPSIS

    void Instruction::clearValues()

DESCRIPTION

    This function clears the values of all of the class variables and sets it to empty

RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
void Instruction::clearValues()
{
    m_Label = "";
    m_OpCode = "";
    m_Operand1 = "";
    m_Operand = "";
    m_Operand2 = "";
} /* void Instruction::clearValues() */
