//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

// Symbol Table Map, Symbol is the key and location is value to the map here
map<string, int> m_symbolTable;

/**/
/*
void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )

NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( const string &a_symbol, int a_loc );
    a_symol         --> symbol of opcode
    a_loc           --> location

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table map.

 RETURNS
 
    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020
*/
/**/
void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );

    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}/* void SymbolTable::AddSymbol( const string &a_symbol, int a_loc ) */


/**/
/*
void SymbolTable::DisplaySymbolTable()

NAME

    void SymbolTable::DisplaySymbolTable() - displays symbol table generated for Pass I

SYNOPSIS

    void SymbolTable::DisplaySymbolTable();  

DESCRIPTION

    This function prints the location and symbols from the Symbol Table Map

 RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020
*/
/**/
void SymbolTable::DisplaySymbolTable()
{
    int index = 0;
    cout << "Symbol Table: " << endl;

    cout << setw(14) << left << "Symbol #" << setw(14) << left << "Symbol" << setw(14) << left << "Location" << endl;
  
    for (map<string, int>::iterator it = m_symbolTable.begin(); it != m_symbolTable.end(); ++it) {
        cout << setw(14) << left << index++ << setw(14) << left << it->first << setw(14) << left << it->second << endl;
    }
    cout << setfill('_') << setw(50) << " "  << endl;
    cout << "\n Press Enter to Continue...." << endl;
    cin.ignore();
}/* void SymbolTable::DisplaySymbolTable() */


/**/
/*
bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc)

NAME

    bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc) - Checks if the symbol is present in Symbol Table

SYNOPSIS

    bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc)
    a_symbol  -----> symbol that is need to be looked up in the table
    a_loc     -----> if the symbol is found in symbol table, it will update the location

DESCRIPTION

    This function iterates the symbol table to check if the symbol exists in 
    symbol table. It also updates the location as the location And returns true if symbol is present
    If the symbol is not present in the symbol table, it will return false. 

 RETURNS

    true if symbol is present and false if symbol is not present in symbol table

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020
*/
/**/
bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc)
{
    map<string, int>::iterator it = m_symbolTable.find(a_symbol);
    if (it != m_symbolTable.end()) {
        a_loc = it->second;
        return true;
    }
    return false;
}/* bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc) */