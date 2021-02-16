//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/**/
/*
FileAccess::FileAccess( int argc, char *argv[] )

NAME

    FileAccess::FileAccess( int argc, char *argv[] ) - Opens the Source file for Reading

SYNOPSIS

    FileAccess::FileAccess( int argc, char *argv[] );
    argc		-->			Total number of command line arguments
    argv		-->			Pointer to the array of arguments passed through the command line

DESCRIPTION

    This constructor will open the file passed as command line argument for reading.
    Error message will be thrown and program terminates if the file was not found
    
RETURNS


AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
// Don't forget to comment the function headers.
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.


    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated." << argv[1]
            << endl;
        exit( 1 ); 
    }
}
// Destructor for FileAccess class Closes the file
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}/* FileAccess::FileAccess( int argc, char *argv[] ) */


/**/
/*
bool FileAccess::GetNextLine( string &a_line )

NAME

    bool FileAccess::GetNextLine( string &a_line ) - Reads the next line from source file

SYNOPSIS

    bool FileAccess::GetNextLine( string &a_line ) 
    a_line	-> string that will contain instructions to read

DESCRIPTION

   This function returns true if it successfully read the next line from the provided source code

RETURNS

    Returns true if read was successful. If it was not it returns false

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
// Get the next line from the file.
bool FileAccess::GetNextLine( string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_line );

    // Return indicating success.
    return true;
} /* bool FileAccess::GetNextLine( string &a_line ) */


/**/
/*
void FileAccess::rewind( )

NAME

    void FileAccess::rewind( ) - Clean all flags

SYNOPSIS

    void FileAccess::rewind( )

DESCRIPTION

    This function clears all flags and go back to the beginning of the file again

RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
void FileAccess::rewind( )
{
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
} /* void FileAccess::rewind( ) */
    
