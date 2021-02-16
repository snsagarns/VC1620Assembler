//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

/**/
/*
Assembler::Assembler( int argc, char *argv[] )

NAME

    Assembler::Assembler(int argc, char *argv[]) - Constructor of the assembler that takes in the file name as its arguments

SYNOPSIS

    Assembler::Assembler(int argc, char *argv[])
    argc		-->			Total number of arguments in the command line
    argv		-->			Pointer to the array of arguments passed through the command line

DESCRIPTION

    This function is the constructor of Assembler class. Note: we are passing argc and argv to the file access constructor.

RETURNS

    
AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
    // See Main Program
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler( )
{

} /*  Assembler::Assembler(int argc, char *argv[]) */


/**/
/*
void Assembler::PassI( )

NAME
    
    Assembler::PassI() - Initiates the first pass which adds symbols in symbol table

SYNOPSIS

  	void Assembler::PassI()

DESCRIPTION

    This function establishes the location of the labels. It will store the location of all the labels required for
    the assembler. However, it doesn't handle any error, Errors are handled in Pass II

RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {
        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine( line ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st= m_inst.ParseInstruction( line );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.  Currently this is only comments.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
	    }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
} /* void Assembler::PassI() */


/**/
/*
void Assembler::PassII( )

NAME
    
    Assembler::PassII() Directs Translation, and Direct Error Check

SYNOPSIS

    void Assembler::PassII()

DESCRIPTION

    This function uses symbol table of previous Pass and directs the translation of the source code for VC-1620 Computer. 
    Pass II directs translation, records any error encountered and stores the translated instructions in a vector of pair for
    passing into the emulator program. It also directs to print the translation of each line with actual statement and report errors 
    at the end (if there are any)
 

RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
void Assembler::PassII( )
{
    m_facc.rewind();      // Rewinds to the beginning of the file
    int loc = 0;        // Tracks the location of the instructions to be generated.
    bool is_end = false; // Flag to indicate if the code has hit the end statement
    
    Errors::InitErrorReporting();   

    // Clearing the vector which hold the pair of location and content for passing into emulator
    m_machinecode.clear();

    // Print the header for the Translation of Program
    cout << "Translation of Program:" << endl;
    cout << setfill(' ') << setw(14) <<left << "Location" << setw(15) << left << "Contents" << setw(18) << left<< "Original Statement" << endl;
  
    // Successively process each line of source code.
    for (; ; ) {

        // Read the next line from the source file
        string line;
        if (!m_facc.GetNextLine(line)){

            if (is_end == true)
                break;

            // Report error: Missing an END Statement
            Errors::RecordError ("Location: " + to_string(loc) + " -> Missing an END statement");
            break;
        }

        pair<int, string> translation = m_inst.TranslateInstruction(line, loc);

        // Set the is_end flag to true when end statment appears
        if (translation == pair <int, string>(0, "end"))
            is_end = true;

        // Do not push_back the pair onto vector if there is no valid machine code
        else if (translation != pair<int, string>(0, "n/a"))
            m_machinecode.push_back(translation);

        // get the location of next instruction 
         loc = m_inst.LocationNextInstruction(loc);
    }

    if (!Errors::isEmptyError())
        Errors::DisplayErrors();

    cout << setfill('_') << setw(50) << "" << endl;
    cout << "\n Press Enter to Continue..\n" << endl;
    cin.ignore();
}/* void Assembler::PassII() */


/**/
/*
    void Assembler::RunProgramInEmulator()

NAME

   void Assembler::RunProgramInEmulator() - Runs Emulator on Translated Code

SYNOPSIS

    void Assembler::RunProgramInEmulator()

DESCRIPTION

    This function runs the emulator of program and also reports if any errors are encountered during emulation

RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
void Assembler::RunProgramInEmulator()
{
    cout << " Results from emulating program:" << endl;
    // Terminates the emulation if there are errors
    if(!Errors::isEmptyError()){
        cout << "Errors were encountered. Exiting the emulation of program";
        return;
    }

    // Insert the machine code into the emulator class and report error
    for (vector <pair<int, string>> ::iterator it = m_machinecode.begin(); it != m_machinecode.end(); ++it) {
        bool insert_check = m_emul.insertMemory(it->first, stoll(it->second));

        if (insert_check == false)
            Errors::RecordError("Error inserting the command: " + to_string(it->first) + " " + it->second + " in emulator");

        }
        // Run Emulator program and check if any error encountered
        bool run_check = m_emul.runProgram();
    
    if (run_check == false) 
            Errors::RecordError("Errors running the Emulator ");

    // Display any errors encountered during emulation
    if (!Errors::isEmptyError())
            Errors::DisplayErrors();

    cout << " Press Enter to Continue...." << endl;
    cin.ignore();
}/* void Assembler::RunProgramInEmulator() */


