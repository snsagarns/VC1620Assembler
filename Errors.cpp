#include "stdafx.h"
#include "Errors.h"

// Vector to store and record the error messages
vector<string> Errors::m_ErrorMsgs;


/**/
/*
void Errors::InitErrorReporting()

NAME

    void Errors::InitErrorReporting() - clears error message vector 

SYNOPSIS

    void Errors::InitErrorReporting();

DESCRIPTION

    This function initiates the Error Reporting and also erasea all previous errors from vector

RETURNS
    
    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
// Initializes error reports.
void Errors::InitErrorReporting()
{
    m_ErrorMsgs.clear();
}/* void Errors::InitErrorReporting() */


/**/
/*
void Errors::RecordError(const string& a_emsg)

NAME

    void Errors::RecordError(const string& a_emsg) - Stores the error messages in vector

SYNOPSIS

    void Errors::RecordError(const string& a_emsg)
    a_emsg  ---> Constant String Error Messages generated at different section of programs

DESCRIPTION

    This function records any type of errors found while parsing, translating or emulating the VC1620 Assembler 
    It pushes back error into vector

RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
void Errors::RecordError(const string& a_emsg)
{
    m_ErrorMsgs.push_back(a_emsg);
}/* void Errors::RecordError(const string& a_emsg) */


/**/
/*
void Errors:: DisplayErrors()

NAME

    void Errors:: DisplayErrors()    - Displays Errors Generated at different points of program

SYNOPSIS

    void Errors:: DisplayErrors()

DESCRIPTION

    This function displays/ prints the errors from the vector generated at different point of program like parsing, translating and emulating

RETURNS

    VOID

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
void Errors:: DisplayErrors()
{
    for (size_t i = 0; i < m_ErrorMsgs.size(); i++)
    {
        cerr << m_ErrorMsgs[i] << endl;
    }
    m_ErrorMsgs.clear();
}; /* void Errors:: DisplayErrors() */


/**/
/*
bool Errors::isEmptyError()

NAME

    bool Errors::isEmptyError() - Checks if the error vector is empty 

SYNOPSIS

    bool Errors::isEmptyError()

DESCRIPTION

    This function checks if there are any errors present. If it's empty it returns true

RETURNS

    Returns true if error messages are empty. Otherwise returns false

AUTHOR

    Sagar Neupane

DATE

    11:51 PM 12/21/2020

*/
/**/
bool Errors::isEmptyError()
{
    return m_ErrorMsgs.empty();
}/* bool Errors::isEmptyError() */