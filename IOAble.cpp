/* Citation and Sources...
Final Project Milestone 5
Module: IOAble
Filename: IOAble.cpp
Version 1.0
Author	George Petrovski
Revision History
-----------------------------------------------------------
Date            Reason
2021/08/02      First Submission
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "IOAble.h"

namespace sdds
{
    std::ostream& operator<<(std::ostream& ostr, const IOAble& IOdata)
    {
        IOdata.write(ostr);
        return ostr;
    }
    std::istream& operator>>(std::istream& istr, IOAble& IOdata)
    {
        IOdata.read(istr);
        return istr;
    }
    IOAble::~IOAble(){ }
}