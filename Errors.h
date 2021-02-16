//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <vector>
#include <string>

class Errors {
public:
    // Initializes error reports.
    static void InitErrorReporting();

    // Records an error message. push back errors in vector
    static void RecordError(const string& a_emsg);

    // Displays the collected error message.
    static void DisplayErrors();

    //checks if there are any errors
    static bool isEmptyError();

private:

    static vector<string> m_ErrorMsgs;  // This must be declared in the .cpp file.  Why?
};

#endif