/* Citation and Sources...
Final Project Milestone 5
Module: IOAble
Filename: IOAble.h
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

#ifndef SDDS_IOABLE_H_
#define SDDS_IOABLE_H_
#include <iostream>

namespace sdds
{
    class IOAble
    {
        public:
            virtual std::ostream& csvWrite(std::ostream& ostr)const = 0;
            virtual std::istream& csvRead(std::istream& istr) = 0;
            virtual std::ostream& write(std::ostream& ostr)const = 0;
            virtual std::istream& read(std::istream& istr) = 0;
            virtual ~IOAble();
    };

    std::ostream& operator<<(std::ostream& ostr, const IOAble& IOdata);
    std::istream& operator>>(std::istream& istr, IOAble& IOdata);
}

#endif // !SDDS_IOABLE_H_
